/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "obr/renderer/obr_impl.h"

#include <cmath>
#include <cstddef>
#include <utility>
#include <vector>

#include "absl/status/status_matchers.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "obr/ambisonic_encoder/ambisonic_encoder.h"
#include "obr/audio_buffer/audio_buffer.h"
#include "obr/common/test_util.h"
#include "obr/renderer/audio_element_type.h"

namespace obr {
namespace {

using ::absl_testing::IsOk;

/*!\brief Create AudioBuffer with Kronecker delta encoded to Ambisonics.
 *
 *  \param num_frames Number of samples in the buffer.
 *  \param azimuth Azimuth angle in degrees.
 *  \param elevation Elevation angle in degrees.
 *  \param distance Distance in meters.
 *  \param ambisonic_order Ambisonic order.
 *
 *  \return AudioBuffer with Kronecker delta encoded to Ambisonics.
 */
AudioBuffer GetKroneckerDeltaEncodedToAmbisonics(const size_t num_frames,
                                                 const float azimuth,
                                                 const float elevation,
                                                 const float distance,
                                                 const int ambisonic_order) {
  AudioBuffer mono_signal(1, num_frames);
  AudioBuffer output_buffer((ambisonic_order + 1) * (ambisonic_order + 1),
                            num_frames);

  GenerateDiracImpulseFilter(0, &mono_signal[0]);

  AmbisonicEncoder encoder(1, ambisonic_order);
  encoder.SetSource(0, 1.0f, azimuth, elevation, distance);
  encoder.ProcessPlanarAudioData(mono_signal, &output_buffer);

  return output_buffer;
}

/*!\brief Get broadband ILD.
 *
 *  \param left Left channel.
 *  \param right Right channel.
 *
 *  \return Broadband ILD.
 */
double GetBroadbandILD(const AudioBuffer::Channel& left,
                       const AudioBuffer::Channel& right) {
  // Get Energy of the left and right channels.
  const double energy_left = CalculateSignalEnergy(left);
  const double energy_right = CalculateSignalEnergy(right);

  // Calculate ILD.
  const double ILD = 10.0 * std::log10(energy_left / energy_right);
  return ILD;
}

// Test initialization of the ObrImpl class.
TEST(ObrImplTest, TestInitialization) {
  const int kBufferSizePerChannel = 12;
  const int kSamplingRate = 48000;

  ObrImpl renderer(kBufferSizePerChannel, kSamplingRate);
  EXPECT_EQ(renderer.GetBufferSizePerChannel(), kBufferSizePerChannel);
  EXPECT_EQ(renderer.GetSamplingRate(), kSamplingRate);
  EXPECT_EQ(renderer.GetNumberOfInputChannels(), 0);
  EXPECT_EQ(renderer.GetNumberOfOutputChannels(), 2);
}

// Test adding and removing 1 audio element.
TEST(ObrImplTest, TestAddAndRemoveAudioElement) {
  const int kBufferSizePerChannel = 12;
  const int kSamplingRate = 48000;

  ObrImpl renderer(kBufferSizePerChannel, kSamplingRate);
  EXPECT_THAT(renderer.AddAudioElement(AudioElementType::k3OA), IsOk());
  EXPECT_EQ(renderer.GetNumberOfInputChannels(), 16);

  EXPECT_THAT(renderer.RemoveLastAudioElement(), IsOk());
  EXPECT_EQ(renderer.GetNumberOfInputChannels(), 0);
}

// Test adding 3OA and 7.1.4 Audio Elements.
TEST(ObrImplTest, TestAddAudioElements) {
  const int kBufferSizePerChannel = 12;
  const int kSamplingRate = 48000;

  ObrImpl renderer(kBufferSizePerChannel, kSamplingRate);
  EXPECT_THAT(renderer.AddAudioElement(AudioElementType::k3OA), IsOk());
  EXPECT_EQ(renderer.GetNumberOfInputChannels(), 16);

  // Expect fail.
  EXPECT_FALSE(
      renderer.AddAudioElement(AudioElementType::kLayout7_1_4_ch).ok());
  EXPECT_THAT(renderer.RemoveLastAudioElement(), IsOk());
  EXPECT_FALSE(renderer.RemoveLastAudioElement().ok());
  EXPECT_EQ(renderer.GetNumberOfInputChannels(), 0);
}

// Test rendering of Ambisonic scenes containing a Kronecker delta at different
// azimuths.
TEST(ObrImplTest, TestRenderAmbisonicsAndMeasureBroadbandILD) {
  const size_t kTestSignalLength = 1000;
  const size_t num_frames = kTestSignalLength;
  const double kILDAccuracyThresholdDb = 3;

  std::vector<AudioElementType> audio_elements = {
      AudioElementType::k1OA, AudioElementType::k2OA, AudioElementType::k3OA,
      AudioElementType::k4OA, AudioElementType::k5OA, AudioElementType::k6OA,
      AudioElementType::k7OA,
  };

  const std::pair<float, double> azimuth_ILDs[] = {
      {0.0f, 0.0}, {90.0f, 12.0}, {180.0f, 0.0}, {270.0f, -12.0}};

  for (const auto audio_element : audio_elements) {
    for (const auto& azimuthILD : azimuth_ILDs) {
      const int ambisonic_order = GetAmbisonicOrder(audio_element).value();
      const float azimuth = azimuthILD.first;
      const float elevation = 0.0f;
      const float distance = 1.0f;
      const double expected_ILD = azimuthILD.second;

      ObrImpl renderer(num_frames, 48000);
      EXPECT_THAT(renderer.AddAudioElement(audio_element), IsOk());

      AudioBuffer test_ambisonic_scene = GetKroneckerDeltaEncodedToAmbisonics(
          kTestSignalLength, azimuth, elevation, distance, ambisonic_order);
      AudioBuffer binaural_output_buffer(2, num_frames);

      renderer.Process(test_ambisonic_scene, &binaural_output_buffer);

      // Measure ILD.
      const double ILD =
          GetBroadbandILD(binaural_output_buffer[0], binaural_output_buffer[1]);
      EXPECT_NEAR(ILD, expected_ILD, kILDAccuracyThresholdDb);
    }
  }
}

// Fails when input AudioBuffer has different number of channels than the
// declared number of input channels.
TEST(ObrImplTest, TestProcessAudioBufferWithWrongNumberOfChannels) {
  const int kBufferSizePerChannel = 12;
  const int kSamplingRate = 48000;

  ObrImpl renderer(kBufferSizePerChannel, kSamplingRate);
  EXPECT_THAT(renderer.AddAudioElement(AudioElementType::k3OA), IsOk());

  AudioBuffer input_buffer(17, kBufferSizePerChannel);
  AudioBuffer output_buffer(2, kBufferSizePerChannel);

  EXPECT_DEATH(renderer.Process(input_buffer, &output_buffer), "");
}

// Fails when input AudioBuffer has different number of frames than the declared
// buffer size.
TEST(ObrImplTest, TestProcessAudioBufferWithWrongBufferSize) {
  const int kBufferSizePerChannel = 12;
  const int kSamplingRate = 48000;

  ObrImpl renderer(kBufferSizePerChannel, kSamplingRate);
  EXPECT_THAT(renderer.AddAudioElement(AudioElementType::k3OA), IsOk());

  AudioBuffer input_buffer(16, kBufferSizePerChannel + 1);
  AudioBuffer output_buffer(2, kBufferSizePerChannel);

  EXPECT_DEATH(renderer.Process(input_buffer, &output_buffer), "");
}

// Fails when output AudioBuffer is not initialized.
TEST(ObrImplTest, TestProcessAudioBufferWithUninitializedOutputBuffer) {
  const int kBufferSizePerChannel = 12;
  const int kSamplingRate = 48000;

  ObrImpl renderer(kBufferSizePerChannel, kSamplingRate);
  EXPECT_THAT(renderer.AddAudioElement(AudioElementType::k3OA), IsOk());

  AudioBuffer input_buffer(16, kBufferSizePerChannel);

  EXPECT_DEATH(renderer.Process(input_buffer, nullptr), "");
}

// Fails when output AudioBuffer has different number of channels than 2.
TEST(ObrImplTest, TestProcessAudioBufferWithWrongNumberOfOutputChannels) {
  const int kBufferSizePerChannel = 12;
  const int kSamplingRate = 48000;

  ObrImpl renderer(kBufferSizePerChannel, kSamplingRate);
  EXPECT_THAT(renderer.AddAudioElement(AudioElementType::k3OA), IsOk());

  AudioBuffer input_buffer(16, kBufferSizePerChannel);
  AudioBuffer output_buffer(3, kBufferSizePerChannel);

  EXPECT_DEATH(renderer.Process(input_buffer, &output_buffer), "");
}

// Fails when output AudioBuffer has different number of frames than the
// declared buffer size.
TEST(ObrImplTest, TestProcessAudioBufferWithWrongOutputBufferSize) {
  const int kBufferSizePerChannel = 12;
  const int kSamplingRate = 48000;

  ObrImpl renderer(kBufferSizePerChannel, kSamplingRate);
  EXPECT_THAT(renderer.AddAudioElement(AudioElementType::k3OA), IsOk());

  AudioBuffer input_buffer(16, kBufferSizePerChannel);
  AudioBuffer output_buffer(2, kBufferSizePerChannel + 1);

  EXPECT_DEATH(renderer.Process(input_buffer, &output_buffer), "");
}

}  // namespace
}  // namespace obr

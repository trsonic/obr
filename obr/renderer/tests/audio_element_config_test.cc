/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "obr/renderer/audio_element_config.h"

#include "gtest/gtest.h"
#include "obr/renderer/audio_element_type.h"

namespace obr {
namespace {

// Test creation of an audio element configuration.
TEST(AudioElementConfigTest, CreateAudioElementConfig) {
  AudioElementConfig audio_element_config(AudioElementType::kLayoutMono);
  EXPECT_EQ(audio_element_config.GetType(), AudioElementType::kLayoutMono);

  audio_element_config.SetFirstChannelIndex(0);
  EXPECT_EQ(audio_element_config.GetFirstChannelIndex(), 0);
  EXPECT_EQ(audio_element_config.GetNumberOfInputChannels(), 1);

  auto input_channels = audio_element_config.GetLoudspeakerChannels();
  EXPECT_EQ(input_channels.size(), 1);
}

// Test `kObjectMono` audio element configuration.
TEST(AudioElementConfigTest, CreateMonoObjectAudioElementConfig) {
  AudioElementConfig audio_element_config(AudioElementType::kObjectMono);
  EXPECT_EQ(audio_element_config.GetType(), AudioElementType::kObjectMono);

  // Set azimuth, elevation, and distance.
  for (auto& channel : audio_element_config.GetObjectChannels()) {
    channel.SetAzimuth(0);
    channel.SetElevation(0);
    channel.SetDistance(1);
  }
}

}  // namespace
}  // namespace obr

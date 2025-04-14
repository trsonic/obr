/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "obr/ambisonic_binaural_decoder/ambisonic_binaural_decoder.h"

#include <cstddef>

#include "absl/log/check.h"
#include "obr/ambisonic_binaural_decoder/fft_manager.h"
#include "obr/ambisonic_binaural_decoder/partitioned_fft_filter.h"
#include "obr/audio_buffer/audio_buffer.h"
#include "obr/common/constants.h"
#include "obr/common/misc_math.h"

namespace obr {

AmbisonicBinauralDecoder::AmbisonicBinauralDecoder(
    const AudioBuffer& sh_hrirs_L, const AudioBuffer& sh_hrirs_R,
    size_t frames_per_buffer, FftManager* fft_manager)
    : fft_manager_(fft_manager),
      freq_input_(kNumMonoChannels,
                  NextPowTwo(frames_per_buffer) * kNumStereoChannels),
      filtered_input_(kNumMonoChannels, frames_per_buffer) {
  CHECK_NE(fft_manager_, nullptr);
  CHECK_NE(frames_per_buffer, 0U);
  const size_t num_channels = sh_hrirs_L.num_channels();
  const size_t filter_size = sh_hrirs_L.num_frames();
  CHECK_NE(num_channels, 0U);
  CHECK_NE(filter_size, 0U);

  // Setup left ear filters.
  sh_hrir_filters_L_.reserve(num_channels);
  for (size_t i = 0; i < num_channels; ++i) {
    sh_hrir_filters_L_.emplace_back(
        new PartitionedFftFilter(filter_size, frames_per_buffer, fft_manager_));
    sh_hrir_filters_L_[i]->SetTimeDomainKernel(sh_hrirs_L[i]);
  }

  // Setup right ear filters.
  CHECK_EQ(sh_hrirs_R.num_channels(), num_channels);
  sh_hrir_filters_R_.reserve(num_channels);
  for (size_t i = 0; i < num_channels; ++i) {
    sh_hrir_filters_R_.emplace_back(
        new PartitionedFftFilter(filter_size, frames_per_buffer, fft_manager_));
    sh_hrir_filters_R_[i]->SetTimeDomainKernel(sh_hrirs_R[i]);
  }
}

void AmbisonicBinauralDecoder::ProcessAudioBuffer(const AudioBuffer& input,
                                                  AudioBuffer* output) {
  CHECK_EQ(input.num_channels(), sh_hrir_filters_L_.size());
  CHECK_EQ(input.num_channels(), sh_hrir_filters_R_.size());
  CHECK_NE(output, nullptr);
  CHECK_EQ(input.num_frames(), output->num_frames());
  CHECK_EQ(output->num_channels(), kNumBinauralChannels);

  output->Clear();
  AudioBuffer::Channel* output_channel_0 = &(*output)[0];
  AudioBuffer::Channel* output_channel_1 = &(*output)[1];

  // Separate left/right ear signal processing.
  AudioBuffer::Channel* freq_input_channel_L = &freq_input_[0];
  AudioBuffer::Channel* freq_input_channel_R = &freq_input_[0];
  AudioBuffer::Channel* filtered_input_channel_L = &filtered_input_[0];
  AudioBuffer::Channel* filtered_input_channel_R = &filtered_input_[0];

  for (size_t channel = 0; channel < input.num_channels(); ++channel) {
    fft_manager_->FreqFromTimeDomain(input[channel], freq_input_channel_L);
    sh_hrir_filters_L_[channel]->Filter(*freq_input_channel_L);
    sh_hrir_filters_L_[channel]->GetFilteredSignal(filtered_input_channel_L);
    *output_channel_0 += *filtered_input_channel_L;

    fft_manager_->FreqFromTimeDomain(input[channel], freq_input_channel_R);
    sh_hrir_filters_R_[channel]->Filter(*freq_input_channel_R);
    sh_hrir_filters_R_[channel]->GetFilteredSignal(filtered_input_channel_R);
    *output_channel_1 += *filtered_input_channel_R;
  }
}

}  // namespace obr

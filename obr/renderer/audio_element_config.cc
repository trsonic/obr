/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "audio_element_config.h"

#include <cstddef>
#include <string>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "obr/common/constants.h"
#include "obr/renderer/audio_element_type.h"
#include "obr/renderer/input_channel_config.h"
#include "obr/renderer/loudspeaker_layouts.h"

namespace obr {

AudioElementConfig::AudioElementConfig(AudioElementType type)
    : type_(type),
      first_channel_index_(0),
      number_of_input_channels_(0),
      binaural_filters_ambisonic_order_(0) {
  // Configure the audio element based on the requested type.
  if (IsAmbisonicsType(type)) {
    // Get the Ambisonic order from the type.
    auto returned_order = GetAmbisonicOrder(type);
    CHECK_OK(returned_order);
    int order = returned_order.value();
    CHECK_GE(order, kMinSupportedAmbisonicOrder);
    CHECK_LE(order, kMaxSupportedAmbisonicOrder);

    // Set binaural filters matching the Ambisonic order of the input.
    // Downscaling / upscaling of Ambisonic scenes is not supported.
    binaural_filters_ambisonic_order_ = order;
    number_of_input_channels_ = (binaural_filters_ambisonic_order_ + 1) *
                                (binaural_filters_ambisonic_order_ + 1);

    // Populate the list of Ambisonic input channels.
    for (size_t i = 0; i < number_of_input_channels_; ++i) {
      AmbisonicSceneInputChannel ambisonic_channel("kACN" + std::to_string(i));
      ambisonic_channels_.push_back(ambisonic_channel);
    }

  } else if (IsLoudspeakerLayoutType(type)) {
    // Check if sub_type matches any of the available loudspeaker layouts.
    LoudspeakerLayouts lspk_layouts;
    loudspeaker_channels_ = lspk_layouts.getLoudspeakerLayout(type);

    // Set binaural filters to the highest order available.
    binaural_filters_ambisonic_order_ = kMaxSupportedAmbisonicOrder;
    number_of_input_channels_ = loudspeaker_channels_.size();
  } else if (IsObjectType(type)) {
    if (type == AudioElementType::kObjectMono) {
      // Create a single input channel.
      AudioObjectInputChannel input_channel("kMono", 0.0f, 0.0f, 1.0f);
      object_channels_.push_back(input_channel);
    } else {
      // TODO(b/402012112): Add Stereo objects with spread, rotation and
      //                    balance parameters additionally.
      LOG(ERROR) << "Unsupported object type.";
    }

    // Set binaural filters to the highest order available.
    binaural_filters_ambisonic_order_ = kMaxSupportedAmbisonicOrder;
    number_of_input_channels_ = object_channels_.size();

  } else {
    LOG(ERROR) << "Unknown audio element type.";
  }

  // Set the first channel index and update the channel indices for all.
  SetFirstChannelIndex(0);
}

AudioElementType AudioElementConfig::GetType() const { return type_; }

absl::StatusOr<absl::string_view> AudioElementConfig::GetTypeStr() {
  const auto type_string = GetAudioElementTypeStr(type_);
  if (!type_string.ok()) {
    return type_string.status();
  }
  return type_string.value();
}

void AudioElementConfig::SetFirstChannelIndex(size_t first_channel) {
  first_channel_index_ = first_channel;

  // Update the channel indices for all channels.
  for (size_t i = 0; i < ambisonic_channels_.size(); ++i) {
    ambisonic_channels_[i].SetChannelIndex(first_channel + i);
  }
  for (size_t i = 0; i < loudspeaker_channels_.size(); ++i) {
    loudspeaker_channels_[i].SetChannelIndex(first_channel + i);
  }
  for (size_t i = 0; i < object_channels_.size(); ++i) {
    object_channels_[i].SetChannelIndex(first_channel + i);
  }
}

size_t AudioElementConfig::GetFirstChannelIndex() const {
  return first_channel_index_;
}

size_t AudioElementConfig::GetNumberOfInputChannels() const {
  return number_of_input_channels_;
}

std::vector<AmbisonicSceneInputChannel>&
AudioElementConfig::GetAmbisonicChannels() {
  return ambisonic_channels_;
}

std::vector<LoudspeakerLayoutInputChannel>&
AudioElementConfig::GetLoudspeakerChannels() {
  return loudspeaker_channels_;
}

std::vector<AudioObjectInputChannel>& AudioElementConfig::GetObjectChannels() {
  return object_channels_;
}

int AudioElementConfig::GetBinauralFiltersAmbisonicOrder() const {
  return binaural_filters_ambisonic_order_;
}

}  // namespace obr

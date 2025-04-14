/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "obr/audio_buffer/channel_view.h"

#include "absl/log/check.h"
#include "obr/audio_buffer/simd_utils.h"

namespace obr {

ChannelView& ChannelView::operator+=(const ChannelView& other) {
  DCHECK_EQ(other.size(), size_);
  DCHECK(enabled_);
  float* this_sample = begin();
  const float* other_sample = other.begin();
  AddPointwise(size_, other_sample, this_sample, this_sample);
  return *this;
}

ChannelView& ChannelView::operator-=(const ChannelView& other) {
  DCHECK_EQ(other.size(), size_);
  DCHECK(enabled_);
  float* this_sample = begin();
  const float* other_sample = other.begin();
  SubtractPointwise(size_, other_sample, this_sample, this_sample);
  return *this;
}

ChannelView& ChannelView::operator*=(const ChannelView& other) {
  DCHECK_EQ(other.size(), size_);
  DCHECK(enabled_);
  float* this_sample = begin();
  const float* other_sample = other.begin();
  MultiplyPointwise(size_, other_sample, this_sample, this_sample);
  return *this;
}

}  // namespace obr

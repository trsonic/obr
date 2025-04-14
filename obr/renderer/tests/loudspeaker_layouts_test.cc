/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "obr/renderer/loudspeaker_layouts.h"

#include "gtest/gtest.h"
#include "obr/renderer/audio_element_type.h"

namespace obr {
namespace {

// Test that the loudspeaker layout is correctly returned for a given layout
// name.
TEST(LoudspeakerLayoutsTest, GetLoudspeakerLayout) {
  LoudspeakerLayouts loudspeaker_layouts;

  auto layout =
      loudspeaker_layouts.getLoudspeakerLayout(AudioElementType::kLayoutMono);
  EXPECT_EQ(layout.size(), 1);
  EXPECT_EQ(layout[0].GetID(), "kC");

  layout =
      loudspeaker_layouts.getLoudspeakerLayout(AudioElementType::kLayoutStereo);
  EXPECT_EQ(layout.size(), 2);
  EXPECT_EQ(layout[0].GetID(), "kL30");
  EXPECT_EQ(layout[1].GetID(), "kR30");
}

}  // namespace
}  // namespace obr

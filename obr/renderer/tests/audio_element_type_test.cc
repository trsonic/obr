/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "obr/renderer/audio_element_type.h"

#include <string>
#include <vector>

#include "absl/status/status_matchers.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace obr {
namespace {

using ::absl_testing::IsOkAndHolds;

// Test that the AudioElementType enum is correctly converted to a string.
TEST(AudioElementTypeTest, AudioElementTypeToString) {
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::k1OA),
              IsOkAndHolds("k1OA"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::k2OA),
              IsOkAndHolds("k2OA"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::k3OA),
              IsOkAndHolds("k3OA"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::k4OA),
              IsOkAndHolds("k4OA"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::k5OA),
              IsOkAndHolds("k5OA"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::k6OA),
              IsOkAndHolds("k6OA"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::k7OA),
              IsOkAndHolds("k7OA"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayoutMono),
              IsOkAndHolds("kLayoutMono"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayoutStereo),
              IsOkAndHolds("kLayoutStereo"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout3_1_2_ch),
              IsOkAndHolds("kLayout3_1_2_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout5_1_0_ch),
              IsOkAndHolds("kLayout5_1_0_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout5_1_2_ch),
              IsOkAndHolds("kLayout5_1_2_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout5_1_4_ch),
              IsOkAndHolds("kLayout5_1_4_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout7_1_0_ch),
              IsOkAndHolds("kLayout7_1_0_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout7_1_2_ch),
              IsOkAndHolds("kLayout7_1_2_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout7_1_4_ch),
              IsOkAndHolds("kLayout7_1_4_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout9_1_0_ch),
              IsOkAndHolds("kLayout9_1_0_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout9_1_2_ch),
              IsOkAndHolds("kLayout9_1_2_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout9_1_4_ch),
              IsOkAndHolds("kLayout9_1_4_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kLayout9_1_6_ch),
              IsOkAndHolds("kLayout9_1_6_ch"));
  EXPECT_THAT(GetAudioElementTypeStr(AudioElementType::kObjectMono),
              IsOkAndHolds("kObjectMono"));
}

// Test that the AudioElementType string is correctly converted to an enum.
TEST(AudioElementTypeTest, AudioElementTypeFromString) {
  EXPECT_THAT(GetAudioElementTypeFromStr("k1OA"),
              IsOkAndHolds(AudioElementType::k1OA));
  EXPECT_THAT(GetAudioElementTypeFromStr("k2OA"),
              IsOkAndHolds(AudioElementType::k2OA));
  EXPECT_THAT(GetAudioElementTypeFromStr("k3OA"),
              IsOkAndHolds(AudioElementType::k3OA));
  EXPECT_THAT(GetAudioElementTypeFromStr("k4OA"),
              IsOkAndHolds(AudioElementType::k4OA));
  EXPECT_THAT(GetAudioElementTypeFromStr("k5OA"),
              IsOkAndHolds(AudioElementType::k5OA));
  EXPECT_THAT(GetAudioElementTypeFromStr("k6OA"),
              IsOkAndHolds(AudioElementType::k6OA));
  EXPECT_THAT(GetAudioElementTypeFromStr("k7OA"),
              IsOkAndHolds(AudioElementType::k7OA));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayoutMono"),
              IsOkAndHolds(AudioElementType::kLayoutMono));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayoutStereo"),
              IsOkAndHolds(AudioElementType::kLayoutStereo));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout3_1_2_ch"),
              IsOkAndHolds(AudioElementType::kLayout3_1_2_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout5_1_0_ch"),
              IsOkAndHolds(AudioElementType::kLayout5_1_0_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout5_1_2_ch"),
              IsOkAndHolds(AudioElementType::kLayout5_1_2_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout5_1_4_ch"),
              IsOkAndHolds(AudioElementType::kLayout5_1_4_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout7_1_0_ch"),
              IsOkAndHolds(AudioElementType::kLayout7_1_0_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout7_1_2_ch"),
              IsOkAndHolds(AudioElementType::kLayout7_1_2_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout7_1_4_ch"),
              IsOkAndHolds(AudioElementType::kLayout7_1_4_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout9_1_0_ch"),
              IsOkAndHolds(AudioElementType::kLayout9_1_0_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout9_1_2_ch"),
              IsOkAndHolds(AudioElementType::kLayout9_1_2_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout9_1_4_ch"),
              IsOkAndHolds(AudioElementType::kLayout9_1_4_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kLayout9_1_6_ch"),
              IsOkAndHolds(AudioElementType::kLayout9_1_6_ch));
  EXPECT_THAT(GetAudioElementTypeFromStr("kObjectMono"),
              IsOkAndHolds(AudioElementType::kObjectMono));
}

// Test that an invalid AudioElementType string returns an error.
TEST(AudioElementTypeTest, AudioElementTypeFromStringError) {
  EXPECT_FALSE(GetAudioElementTypeFromStr("kInvalid").ok());
}

// Test that a list of available AudioElementTypes is returned.
TEST(AudioElementTypeTest, GetAvailableAudioElementTypesAsStr) {
  const std::vector<std::string> expected = {
      "k1OA",
      "k2OA",
      "k3OA",
      "k4OA",
      "k5OA",
      "k6OA",
      "k7OA",
      "kLayoutMono",
      "kLayoutStereo",
      "kLayout3_1_2_ch",
      "kLayout5_1_0_ch",
      "kLayout5_1_2_ch",
      "kLayout5_1_4_ch",
      "kLayout7_1_0_ch",
      "kLayout7_1_2_ch",
      "kLayout7_1_4_ch",
      "kLayout9_1_0_ch",
      "kLayout9_1_2_ch",
      "kLayout9_1_4_ch",
      "kLayout9_1_6_ch",
      "kObjectMono",
  };
  EXPECT_EQ(GetAvailableAudioElementTypesAsStr(), expected);
}

// Test IsAmbisonicsType.
TEST(AudioElementTypeTest, IsAmbisonicsType) {
  EXPECT_TRUE(IsAmbisonicsType(AudioElementType::k1OA));
  EXPECT_TRUE(IsAmbisonicsType(AudioElementType::k2OA));
  EXPECT_TRUE(IsAmbisonicsType(AudioElementType::k3OA));
  EXPECT_TRUE(IsAmbisonicsType(AudioElementType::k4OA));
  EXPECT_TRUE(IsAmbisonicsType(AudioElementType::k5OA));
  EXPECT_TRUE(IsAmbisonicsType(AudioElementType::k6OA));
  EXPECT_TRUE(IsAmbisonicsType(AudioElementType::k7OA));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayoutMono));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayoutStereo));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout3_1_2_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout5_1_0_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout5_1_2_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout5_1_4_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout7_1_0_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout7_1_2_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout7_1_4_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout9_1_0_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout9_1_2_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout9_1_4_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kLayout9_1_6_ch));
  EXPECT_FALSE(IsAmbisonicsType(AudioElementType::kObjectMono));
}

// Test IsLoudspeakerLayoutType.
TEST(AudioElementTypeTest, IsLoudspeakerLayoutType) {
  EXPECT_FALSE(IsLoudspeakerLayoutType(AudioElementType::k1OA));
  EXPECT_FALSE(IsLoudspeakerLayoutType(AudioElementType::k2OA));
  EXPECT_FALSE(IsLoudspeakerLayoutType(AudioElementType::k3OA));
  EXPECT_FALSE(IsLoudspeakerLayoutType(AudioElementType::k4OA));
  EXPECT_FALSE(IsLoudspeakerLayoutType(AudioElementType::k5OA));
  EXPECT_FALSE(IsLoudspeakerLayoutType(AudioElementType::k6OA));
  EXPECT_FALSE(IsLoudspeakerLayoutType(AudioElementType::k7OA));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayoutMono));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayoutStereo));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout3_1_2_ch));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout5_1_0_ch));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout5_1_2_ch));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout5_1_4_ch));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout7_1_0_ch));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout7_1_2_ch));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout7_1_4_ch));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout9_1_0_ch));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout9_1_2_ch));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout9_1_4_ch));
  EXPECT_TRUE(IsLoudspeakerLayoutType(AudioElementType::kLayout9_1_6_ch));
  EXPECT_FALSE(IsLoudspeakerLayoutType(AudioElementType::kObjectMono));
}

// Test IsObjectType.
TEST(AudioElementTypeTest, IsObjectType) {
  EXPECT_FALSE(IsObjectType(AudioElementType::k1OA));
  EXPECT_FALSE(IsObjectType(AudioElementType::k2OA));
  EXPECT_FALSE(IsObjectType(AudioElementType::k3OA));
  EXPECT_FALSE(IsObjectType(AudioElementType::k4OA));
  EXPECT_FALSE(IsObjectType(AudioElementType::k5OA));
  EXPECT_FALSE(IsObjectType(AudioElementType::k6OA));
  EXPECT_FALSE(IsObjectType(AudioElementType::k7OA));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayoutMono));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayoutStereo));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout3_1_2_ch));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout5_1_0_ch));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout5_1_2_ch));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout5_1_4_ch));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout7_1_0_ch));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout7_1_2_ch));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout7_1_4_ch));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout9_1_0_ch));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout9_1_2_ch));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout9_1_4_ch));
  EXPECT_FALSE(IsObjectType(AudioElementType::kLayout9_1_6_ch));
  EXPECT_TRUE(IsObjectType(AudioElementType::kObjectMono));
}

// Test GetAmbisonicOrder.
TEST(AudioElementTypeTest, GetAmbisonicOrder) {
  EXPECT_THAT(GetAmbisonicOrder(AudioElementType::k1OA), IsOkAndHolds(1));
  EXPECT_THAT(GetAmbisonicOrder(AudioElementType::k2OA), IsOkAndHolds(2));
  EXPECT_THAT(GetAmbisonicOrder(AudioElementType::k3OA), IsOkAndHolds(3));
  EXPECT_THAT(GetAmbisonicOrder(AudioElementType::k4OA), IsOkAndHolds(4));
  EXPECT_THAT(GetAmbisonicOrder(AudioElementType::k5OA), IsOkAndHolds(5));
  EXPECT_THAT(GetAmbisonicOrder(AudioElementType::k6OA), IsOkAndHolds(6));
  EXPECT_THAT(GetAmbisonicOrder(AudioElementType::k7OA), IsOkAndHolds(7));
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayoutMono).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayoutStereo).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout3_1_2_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout5_1_0_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout5_1_2_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout5_1_4_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout7_1_0_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout7_1_2_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout7_1_4_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout9_1_0_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout9_1_2_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout9_1_4_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kLayout9_1_6_ch).ok());
  EXPECT_FALSE(GetAmbisonicOrder(AudioElementType::kObjectMono).ok());
}

}  // namespace

}  // namespace obr

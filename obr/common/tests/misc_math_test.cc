/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "obr/common/misc_math.h"

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <vector>

#include "gtest/gtest.h"

namespace obr {

namespace {

TEST(MiscMath, GreatestCommonDivisorTest) {
  const std::vector<int> a_values = {2, 10, 3, 5, 48000, 7, -2, 2, -3};
  const std::vector<int> b_values = {8, 4, 1, 10, 24000, 13, 6, -6, -9};
  const std::vector<int> expected = {2, 2, 1, 5, 24000, 1, 2, 2, 3};

  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], FindGcd(a_values[i], b_values[i]));
  }
}

TEST(MiscMath, NextPowTwoTest) {
  const std::vector<size_t> inputs = {2, 10, 3, 5, 48000, 7, 23, 32};
  const std::vector<size_t> expected = {2, 16, 4, 8, 65536, 8, 32, 32};

  for (size_t i = 0; i < inputs.size(); ++i) {
    EXPECT_EQ(expected[i], NextPowTwo(inputs[i]));
  }
}

TEST(MiscMath, FastReciprocalSqrtTest) {
  const std::vector<float> kNumbers{130.0f, 13.0f,  1.3f,
                                    0.13f,  0.013f, 0.0013f};
  const float kSqrtEpsilon = 2e-3f;
  for (auto& number : kNumbers) {
    const float actual = std::sqrt(number);
    const float approximate = 1.0f / FastReciprocalSqrt(number);
    EXPECT_LT(std::abs(actual - approximate) / actual, kSqrtEpsilon);
  }
}

TEST(MiscMath, IntegerPow) {
  const float kFloatValue = 1.5f;
  const float kNegativeFloatValue = -3.3f;
  const size_t kSizeTValue = 11U;
  const int kIntValue = 5;
  const int kNegativeIntValue = -13;

  for (int exponent = 0; exponent < 5; ++exponent) {
    EXPECT_FLOAT_EQ(IntegerPow(kFloatValue, exponent),
                    std::pow(kFloatValue, static_cast<float>(exponent)));
    EXPECT_FLOAT_EQ(
        IntegerPow(kNegativeFloatValue, exponent),
        std::pow(kNegativeFloatValue, static_cast<float>(exponent)));
    EXPECT_EQ(IntegerPow(kSizeTValue, exponent),
              std::pow(kSizeTValue, exponent));
    EXPECT_EQ(IntegerPow(kIntValue, exponent), std::pow(kIntValue, exponent));
    EXPECT_EQ(IntegerPow(kNegativeIntValue, exponent),
              std::pow(kNegativeIntValue, exponent));
  }
}

}  // namespace

}  // namespace obr

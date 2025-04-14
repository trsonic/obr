/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "obr/audio_buffer/aligned_allocator.h"

#include <cstddef>
#include <vector>

#include "gtest/gtest.h"

namespace obr {
namespace {

// Helper method to test memory alignment.
template <size_t Alignment>
void TestAlignedAllocator() {
  static const size_t kRuns = 1000;
  for (size_t run = 0; run < kRuns; ++run) {
    std::vector<float, AlignedAllocator<float, Alignment> > aligned_vector(1);
    const bool is_aligned =
        ((reinterpret_cast<size_t>(&aligned_vector[0]) & (Alignment - 1)) == 0);
    EXPECT_TRUE(is_aligned);
  }
}

// Allocates multiple std::vectors using the AlignedAllocator and tests if the
// allocated memory is aligned.
TEST(AlignedAlocatorTest, TestAlignment) {
  TestAlignedAllocator<2>();
  TestAlignedAllocator<4>();
  TestAlignedAllocator<16>();
  TestAlignedAllocator<32>();
  TestAlignedAllocator<64>();
}

}  // namespace
}  // namespace obr

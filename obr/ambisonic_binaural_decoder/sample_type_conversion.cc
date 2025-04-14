/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */
// Prevent Visual Studio from complaining about std::copy_n.
#if defined(_WIN32)
#define _SCL_SECURE_NO_WARNINGS
#endif

#include "obr/ambisonic_binaural_decoder/sample_type_conversion.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>

#include "obr/audio_buffer/simd_utils.h"

namespace obr {

void ConvertPlanarSamples(size_t length, const int16_t* input, float* output) {
  FloatFromInt16(length, input, output);
}

void ConvertPlanarSamples(size_t length, const float* input, float* output) {
  std::copy_n(input, length, output);
}

void ConvertPlanarSamples(size_t length, const float* input, int16_t* output) {
  Int16FromFloat(length, input, output);
}

}  // namespace obr

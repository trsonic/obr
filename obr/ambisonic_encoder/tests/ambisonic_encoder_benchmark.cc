/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

#include "benchmark/benchmark.h"
#include "obr/ambisonic_encoder/ambisonic_encoder.h"
#include "obr/audio_buffer/audio_buffer.h"

namespace obr {
namespace {
// TODO(b/373302873): Remove randomness.

// Measure execution time of coefficient calculation.
void BM_SHCalculation(benchmark::State& state) {
  const size_t number_of_input_channels = 512;
  const size_t ambisonic_order = 7;

  // Create an array of azimuth/elevation pairs with random directions.
  std::vector<std::pair<float, float>> directions;
  for (int i = 0; i < number_of_input_channels; i++) {
    float azimuth = static_cast<float>(rand() / RAND_MAX) * 360.0f;
    float elevation = static_cast<float>(rand() / RAND_MAX) * 180.0f - 90.0f;
    directions.emplace_back(azimuth, elevation);
  }

  // Create an Ambisonic encoder object.
  AmbisonicEncoder encoder(number_of_input_channels, ambisonic_order);

  for (auto _ : state) {
    // Assign sources to the encoder at all available input channels.
    for (size_t i = 0; i < number_of_input_channels; i++) {
      encoder.SetSource(i, 1.0f, directions[i].first, directions[i].second,
                        1.0f);
    }
  }
}

BENCHMARK(BM_SHCalculation);

// Measure matrix multiplication time at different numbers of input channels.
// Test with matrix data set to zeros and filled with random data.
// TODO(b/374695317): Optimise matrix multiplication to avoid multiplication by
//                    columns of zeros (inactive inputs).
void BM_MatrixMultiplication(benchmark::State& state) {
  const size_t buffer_size_per_channel = 256;
  const size_t number_of_input_channels = state.range(0);
  const size_t ambisonic_order = 7;
  const bool fill_with_random_data = state.range(1);

  // Create input buffer
  AudioBuffer input_buffer(number_of_input_channels, buffer_size_per_channel);
  input_buffer.Clear();

  if (fill_with_random_data) {
    for (auto ch = 0; ch < input_buffer.num_channels(); ch++) {
      AudioBuffer::Channel& channel = input_buffer[ch];
      for (float& sample : channel) {
        sample = static_cast<float>(rand() / RAND_MAX) - 0.5f;
      }
    }
  }

  // Create output buffer.
  AudioBuffer output_buffer((ambisonic_order + 1) * (ambisonic_order + 1),
                            buffer_size_per_channel);

  // Create an Ambisonic encoder object.
  AmbisonicEncoder encoder(number_of_input_channels, ambisonic_order);

  // Create an array of azimuth/elevation pairs with random directions.
  std::vector<std::pair<float, float>> directions;
  while (directions.size() < number_of_input_channels) {
    float azimuth = static_cast<float>(rand() / RAND_MAX) * 360.0f;
    float elevation = static_cast<float>(rand() / RAND_MAX) * 180.0f - 90.0f;
    directions.emplace_back(azimuth, elevation);
  }

  // Assign sources to the encoder at all available input channels.
  for (size_t i = 0; i < number_of_input_channels; i++) {
    encoder.SetSource(i, 1.0f, directions[i].first, directions[i].second, 1.0f);
  }

  for (auto _ : state) {
    // Perform matrix multiplication.
    encoder.ProcessPlanarAudioData(input_buffer, &output_buffer);
  }
}

BENCHMARK(BM_MatrixMultiplication)
    ->Args({16, 0})
    ->Args({16, 1})
    ->Args({32, 0})
    ->Args({32, 1})
    ->Args({64, 0})
    ->Args({64, 1})
    ->Args({128, 0})
    ->Args({128, 1});

}  // namespace
}  // namespace obr

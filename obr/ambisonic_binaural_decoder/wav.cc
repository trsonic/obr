/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */
// TODO(b/400661672): Use a common library to handle WAV files.
#include "obr/ambisonic_binaural_decoder/wav.h"

#include <cstddef>
#include <cstdint>
#include <istream>
#include <memory>
#include <utility>
#include <vector>

#include "obr/ambisonic_binaural_decoder/wav_reader.h"

namespace obr {

Wav::Wav(size_t num_channels, int sample_rate,
         std::vector<int16_t>&& interleaved_samples)
    : num_channels_(num_channels),
      sample_rate_(sample_rate),
      interleaved_samples_(interleaved_samples) {}

Wav::~Wav() {}

std::unique_ptr<const Wav> Wav::CreateOrNull(std::istream* binary_stream) {
  WavReader wav_reader(binary_stream);
  const size_t num_total_samples = wav_reader.GetNumTotalSamples();
  if (!wav_reader.IsHeaderValid() || num_total_samples == 0) {
    return nullptr;
  }
  std::vector<int16_t> interleaved_samples(num_total_samples);
  if (wav_reader.ReadSamples(num_total_samples, &interleaved_samples[0]) !=
      num_total_samples) {
    return nullptr;
  }
  return std::unique_ptr<Wav>(new Wav(wav_reader.GetNumChannels(),
                                      wav_reader.GetSampleRateHz(),
                                      std::move(interleaved_samples)));
}

}  // namespace obr

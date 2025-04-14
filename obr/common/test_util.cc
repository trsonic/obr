/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "obr/common/test_util.h"

#include <algorithm>
#include <cmath>
#include <cstddef>

#include "absl/log/check.h"
#include "gtest/gtest.h"
#include "obr/audio_buffer/audio_buffer.h"
#include "obr/common/constants.h"

namespace obr {

namespace {}  // namespace

void GenerateSilence(AudioBuffer::Channel* output) {
  ASSERT_NE(output, nullptr);
  output->Clear();
}

void GenerateSineWave(float frequency_hz, int sample_rate,
                      AudioBuffer::Channel* output) {
  ASSERT_GE(frequency_hz, 0.0f);
  ASSERT_GT(sample_rate, 0);
  ASSERT_NE(output, nullptr);
  for (size_t i = 0; i < output->size(); ++i) {
    const float phase = static_cast<float>(i) * kTwoPi /
                        static_cast<float>(sample_rate) * frequency_hz;
    (*output)[i] = std::sin(phase);
  }
}

void GenerateSawToothSignal(size_t tooth_length_samples,
                            AudioBuffer::Channel* output) {
  ASSERT_GT(tooth_length_samples, 0U);
  ASSERT_NE(output, nullptr);

  for (size_t i = 0; i < output->size(); ++i) {
    (*output)[i] = static_cast<float>(i % tooth_length_samples) /
                       static_cast<float>(tooth_length_samples) * 2.0f -
                   1.0f;
  }
}

void GenerateDiracImpulseFilter(size_t delay_samples,
                                AudioBuffer::Channel* output) {
  ASSERT_NE(output, nullptr);
  ASSERT_LT(delay_samples, output->size());
  ASSERT_NE(output, nullptr);
  output->Clear();
  (*output)[delay_samples] = 1.0f;
}

void GenerateIncreasingSignal(AudioBuffer::Channel* output) {
  ASSERT_NE(output, nullptr);
  for (size_t i = 0; i < output->size(); ++i) {
    (*output)[i] =
        static_cast<float>(i) / static_cast<float>(output->size()) * 2.0f -
        1.0f;
  }
}

size_t ZeroCompare(const AudioBuffer::Channel& signal, float epsilon) {
  for (size_t i = 0; i < signal.size(); ++i) {
    if (std::abs(signal[i]) > epsilon) {
      return i;
    }
  }
  return signal.size();
}

bool CompareAudioBuffers(const AudioBuffer::Channel& buffer_a,
                         const AudioBuffer::Channel& buffer_b, float epsilon) {
  if (buffer_a.size() != buffer_b.size()) {
    return false;
  }
  for (size_t i = 0; i < buffer_a.size(); ++i) {
    if (std::abs(buffer_a[i] - buffer_b[i]) > epsilon) {
      return false;
    }
  }
  return true;
}

size_t DelayCompare(const AudioBuffer::Channel& original_signal,
                    const AudioBuffer::Channel& delayed_signal, size_t delay,
                    float epsilon) {
  if (delay > delayed_signal.size() ||
      (delayed_signal.size() > original_signal.size() + delay)) {
    return 0;
  }
  for (size_t i = delay; i < delayed_signal.size(); ++i) {
    const size_t original_index = i - delay;
    const float difference =
        std::abs(delayed_signal[i] - original_signal[original_index]);
    if (difference > epsilon) {
      return i;
    }
  }
  return delayed_signal.size();
}

bool TestZeroPaddedDelay(const AudioBuffer::Channel& original_signal,
                         const AudioBuffer::Channel& delayed_signal,
                         size_t delay_samples, float epsilon) {
  size_t temp = ZeroCompare(delayed_signal, epsilon);
  if (delay_samples != temp) {
    return false;
  }
  temp = DelayCompare(original_signal, delayed_signal, delay_samples, epsilon);
  if (original_signal.size() != temp) {
    return false;
  }
  return true;
}

double CalculateSignalPeak(const AudioBuffer::Channel& channel) {
  double peak = 0.0;
  for (const float& sample : channel) {
    if (std::abs(sample) > peak) peak = std::abs(sample);
  }

  DCHECK_GT(channel.size(), 0);
  return peak;
}

double CalculateSignalEnergy(const AudioBuffer::Channel& channel) {
  double energy = 0.0;
  for (const float& sample : channel) {
    energy += sample * sample;
  }
  return energy;
}

double CalculateSignalRms(const AudioBuffer::Channel& channel) {
  const double energy = CalculateSignalEnergy(channel);
  DCHECK_GT(channel.size(), 0);
  return std::sqrt(energy / static_cast<double>(channel.size()));
}

double DbFromMagnitude(double magnitude) {
  DCHECK_GT(magnitude, 0.0);
  const double decibel = 20.0 * std::log10(magnitude);
  return decibel;
}

double DbFromPower(double power) {
  DCHECK_GT(power, 0.0);
  const double decibel = 10.0 * std::log10(power);
  return decibel;
}

float MaxCrossCorrelation(const AudioBuffer::Channel& signal_a,
                          const AudioBuffer::Channel& signal_b) {
  CHECK_EQ(signal_a.size(), signal_b.size());
  float output = 0.0f;
  const size_t length = signal_a.size();
  for (size_t i = 0; i < length; ++i) {
    float current = 0.0f;
    for (size_t j = 0; j < length - i - 1; ++j) {
      current += signal_a[j + i] * signal_b[j];
    }
    output = std::max(output, current);
  }
  return output;
}

}  // namespace obr

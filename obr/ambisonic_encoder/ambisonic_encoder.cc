/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */
#include "obr/ambisonic_encoder/ambisonic_encoder.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <vector>

#include "Eigen/Core"
#include "absl/log/check.h"
#include "obr/audio_buffer/audio_buffer.h"
#include "obr/common/ambisonic_utils.h"
#include "obr/common/constants.h"

namespace obr {

AmbisonicEncoder::AmbisonicEncoder(size_t number_of_input_channels,
                                   size_t ambisonic_order)
    : number_of_input_channels_(number_of_input_channels),
      number_of_output_channels_((ambisonic_order + 1) * (ambisonic_order + 1)),
      ambisonic_order_(ambisonic_order),
      alp_generator_(static_cast<int>(ambisonic_order), false, false) {
  CHECK_GT(number_of_input_channels_, 0);
  CHECK_GT(ambisonic_order_, 0);

  // Initialize the encoding matrix.
  encoding_matrix_ =
      Eigen::MatrixXf::Zero(static_cast<int>(number_of_output_channels_),
                            static_cast<int>(number_of_input_channels_));
}

void AmbisonicEncoder::SetSource(size_t input_channel, float gain,
                                 float azimuth, float elevation,
                                 float distance) {
  CHECK_NE(number_of_input_channels_, 0);
  CHECK_NE(number_of_output_channels_, 0);
  CHECK_LT(input_channel, number_of_input_channels_);

  // Check if the key exists in the map.
  if (sources_.find(input_channel) == sources_.end()) {
    // Add the source to the map.
    sources_.insert({input_channel, {0.0, 0.0, 0.0, 0.0}});
  }

  // Check if the source is already set to these properties.
  if (sources_.at(input_channel).gain == gain &&
      sources_.at(input_channel).azimuth == azimuth &&
      sources_.at(input_channel).elevation == elevation &&
      sources_.at(input_channel).distance == distance) {
    return;
  }

  // Update the gain, azimuth, elevation and distance of the source.
  sources_.at(input_channel) = {gain, azimuth, elevation, distance};

  // Calculate the overall gain for the source. Limit the minimum distance to
  // 0.5 m.
  float overall_gain = gain / std::max(distance, 0.5f);

  // Mute the source if the overall gain is less than -120 dB.
  if (overall_gain < kNegative120dbInAmplitude) {
    encoding_matrix_.col(static_cast<int>(input_channel)).setZero();
    return;
  }

  // Get the spherical harmonic coefficients for the given azimuth and
  // elevation.
  std::vector<float> sh_coeffs(number_of_output_channels_);
  GetShCoeffs(azimuth, elevation, ambisonic_order_, sh_coeffs);

  // Scale the spherical harmonic coefficients by the overall gain and update
  // the encoding matrix.
  for (size_t i = 0; i < number_of_output_channels_; i++) {
    encoding_matrix_(static_cast<int>(i), static_cast<int>(input_channel)) =
        sh_coeffs.at(i) * overall_gain;
  }
}

void AmbisonicEncoder::RemoveSource(size_t input_channel) {
  // Remove the source from the map.
  sources_.erase(input_channel);

  // Mute the input channel in the encoding matrix.
  encoding_matrix_.col(static_cast<int>(input_channel)).setZero();
}

void AmbisonicEncoder::ProcessPlanarAudioData(
    const AudioBuffer& input_buffer, AudioBuffer* output_buffer) const {
  // Perform checks.
  CHECK_NE(output_buffer, nullptr);
  CHECK_EQ(number_of_input_channels_, input_buffer.num_channels());
  CHECK_EQ(number_of_output_channels_, output_buffer->num_channels());
  CHECK_EQ(input_buffer.num_frames(), output_buffer->num_frames());

  // Create Eigen maps for the input and output buffers.
  Eigen::Map<const Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic,
                                 Eigen::RowMajor>,
             Eigen::Aligned>
      unencoded_buffer(&input_buffer[0][0], number_of_input_channels_,
                       output_buffer->GetChannelStride());

  Eigen::Map<
      Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>,
      Eigen::Aligned>
      encoded_buffer(&(*output_buffer)[0][0], number_of_output_channels_,
                     input_buffer.GetChannelStride());

  encoded_buffer.noalias() = encoding_matrix_ * unencoded_buffer;
}

void AmbisonicEncoder::GetShCoeffs(float azimuth, float elevation,
                                   size_t ambisonic_order,
                                   std::vector<float>& coeffs) {
  float azimuth_rad = azimuth * kRadiansFromDegrees;
  float elevation_rad = elevation * kRadiansFromDegrees;

  std::vector<float> associated_legendre_polynomials_temp_ =
      alp_generator_.Generate(std::sin(elevation_rad));
  // Compute the actual spherical harmonics using the generated polynomials.
  for (int degree = 0; degree <= ambisonic_order; degree++) {
    for (int order = -degree; order <= degree; order++) {
      const int row = AcnSequence(degree, order);
      if (row == -1) {
        // Skip this spherical harmonic.
        continue;
      }

      const float last_term =
          (order >= 0) ? std::cos(static_cast<float>(order) * azimuth_rad)
                       : std::sin(static_cast<float>(-order) * azimuth_rad);

      coeffs.at(row) =
          Sn3dNormalization(degree, order) *
          associated_legendre_polynomials_temp_[alp_generator_.GetIndex(
              degree, std::abs(order))] *
          last_term;
    }
  }
}

}  // namespace obr

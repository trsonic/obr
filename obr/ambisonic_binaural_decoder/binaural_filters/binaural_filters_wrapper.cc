/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "binaural_filters_wrapper.h"

namespace obr {

BinauralFiltersWrapper::BinauralFiltersWrapper() {}

BinauralFiltersWrapper::~BinauralFiltersWrapper() {}

std::unique_ptr<std::string> BinauralFiltersWrapper::GetFile(
    const std::string& filename) const {
  if (auto file = binaural_filters_1_oa_l_.GetFile(filename)) {
    return file;
  }
  if (auto file = binaural_filters_1_oa_r_.GetFile(filename)) {
    return file;
  }
  if (auto file = binaural_filters_2_oa_l_.GetFile(filename)) {
    return file;
  }
  if (auto file = binaural_filters_2_oa_r_.GetFile(filename)) {
    return file;
  }
  if (auto file = binaural_filters_3_oa_l_.GetFile(filename)) {
    return file;
  }
  if (auto file = binaural_filters_3_oa_r_.GetFile(filename)) {
    return file;
  }
  return nullptr;
}

}  // namespace obr

/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#ifndef BINAURALFILTERSWRAPPER_H_
#define BINAURALFILTERSWRAPPER_H_

#include <memory>
#include <string>

#include <unordered_map>
#include "binaural_filters_1_oa_l.h"
#include "binaural_filters_1_oa_r.h"
#include "binaural_filters_2_oa_l.h"
#include "binaural_filters_2_oa_r.h"
#include "binaural_filters_3_oa_l.h"
#include "binaural_filters_3_oa_r.h"

namespace obr {

class BinauralFiltersWrapper {
 public:
  BinauralFiltersWrapper();
  ~BinauralFiltersWrapper();

  std::unique_ptr<std::string> GetFile(
      const std::string& filename) const;

 private:
  binaural_filters_1_oa_l binaural_filters_1_oa_l_;
  binaural_filters_1_oa_r binaural_filters_1_oa_r_;
  binaural_filters_2_oa_l binaural_filters_2_oa_l_;
  binaural_filters_2_oa_r binaural_filters_2_oa_r_;
  binaural_filters_3_oa_l binaural_filters_3_oa_l_;
  binaural_filters_3_oa_r binaural_filters_3_oa_r_;
};

}  // namespace obr

#endif  // BINAURALFILTERSWRAPPER_H_

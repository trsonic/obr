/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include "binaural_filters_wrapper.h"

namespace obr {

const BinauralFiltersWrapper::AssetMap BinauralFiltersWrapper::kAssetMap = {
  {"1OA_L", filter_files::binaural_filters_1_oa_l_GetContents},
  {"1OA_R", filter_files::binaural_filters_1_oa_r_GetContents},
  {"2OA_L", filter_files::binaural_filters_2_oa_l_GetContents},
  {"2OA_R", filter_files::binaural_filters_2_oa_r_GetContents},
  {"3OA_L", filter_files::binaural_filters_3_oa_l_GetContents},
  {"3OA_R", filter_files::binaural_filters_3_oa_r_GetContents},
  {"4OA_L", filter_files::binaural_filters_4_oa_l_GetContents},
  {"4OA_R", filter_files::binaural_filters_4_oa_r_GetContents},
  {"5OA_L", filter_files::binaural_filters_5_oa_l_GetContents},
  {"5OA_R", filter_files::binaural_filters_5_oa_r_GetContents},
  {"6OA_L", filter_files::binaural_filters_6_oa_l_GetContents},
  {"6OA_R", filter_files::binaural_filters_6_oa_r_GetContents},
  {"7OA_L", filter_files::binaural_filters_7_oa_l_GetContents},
  {"7OA_R", filter_files::binaural_filters_7_oa_r_GetContents},
};

BinauralFiltersWrapper::BinauralFiltersWrapper() {}

BinauralFiltersWrapper::~BinauralFiltersWrapper() {}

std::unique_ptr<std::string> BinauralFiltersWrapper::GetFile(const std::string& filename) const {
  auto it = kAssetMap.find(filename);
  if (it == kAssetMap.end()) {
    return nullptr;
  }
  auto data = it->second();
  return std::make_unique<std::string>(reinterpret_cast<const char*>(data.data()), data.size());
}

}  // namespace obr

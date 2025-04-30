/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#ifndef BINAURAL_FILTERS_2_OA_R_
#define BINAURAL_FILTERS_2_OA_R_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace obr {

// Note this class is automatically generated. Do not modify.
class binaural_filters_2_oa_r {
 public:
  /*!\brief Looks up and retrieves a file from an asset class.
   *
   * \param filename Filename to be retrieved.
   * \return `std::unique_ptr<std::string>` with raw file data. In case of an
   *          error, a nullptr is returned. Caller must take over the ownership of
   *          the returned data.
   */
  std::unique_ptr<std::string> GetFile(const std::string& filename) const;

 private:
  typedef std::unordered_map<std::string, std::vector<unsigned char>>
      AssetDataMap;
  static const AssetDataMap kAssetMap;
};

}  // namespace obr

#endif  // BINAURAL_FILTERS_2_OA_R_

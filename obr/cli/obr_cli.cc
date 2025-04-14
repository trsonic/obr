/*
 * Copyright (c) 2025 Google LLC
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License,
 * which you can find in the LICENSE file, and the Open Binaural Renderer
 * Patent License 1.0, which you can find in the PATENTS file.
 */

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "obr/cli/obr_cli_lib.h"
#include "obr/renderer/audio_element_type.h"

// TODO(b/402659240): Support all input types listed in "audio_element_type.h".
/*!\brief Command line interface for obr.
 *
 * Takes single wav file and renders it to binaural. Combination of
 * multiple wav files (e.g. 7.1.4 + 3OA) as an input is not supported.
 * Only 16-bit wav files are supported.
 * Sample rates different from 48000 Hz were not tested.
 */
ABSL_FLAG(obr::AudioElementType, input_type,
          obr::AudioElementType::kInvalidType,
          "Type of input. Currently `3OA`, `7OA`, `7.1.4 `, and `OBA` are "
          "supported.");
ABSL_FLAG(
    std::string, oba_metadata_file, "",
    "Full path to the textproto file containing object metadata if input type "
    "is `OBA`.");
ABSL_FLAG(std::string, input_file, "", "Full path to the input WAV file.");
ABSL_FLAG(std::string, output_file, "/tmp/output.wav",
          "Full path to the output WAV file.");
ABSL_FLAG(
    uint64_t, buffer_size, 256,
    "Processing buffer size; i.e., number of sample per channel per frame.");

namespace obr {

// TODO(b/402659240): Use `GetAudioElementTypeStringMap()` for flag-parsing too.
bool AbslParseFlag(absl::string_view text, AudioElementType* input_type,
                   std::string* error) {
  if (text.empty()) {
    *error = "No input type specified.";
    return false;
  } else if (text == "3OA") {
    *input_type = AudioElementType::k3OA;
  } else if (text == "7OA") {
    *input_type = AudioElementType::k7OA;
  } else if (text == "7.1.4") {
    *input_type = AudioElementType::kLayout7_1_4_ch;
  } else if (text == "OBA") {
    *input_type = AudioElementType::kObjectMono;
  } else {
    *error = "Unsupported input type.";
    return false;
  }
  return true;
}

std::string AbslUnparseFlag(AudioElementType input_type) {
  switch (input_type) {
    using enum AudioElementType;
    case k3OA:
      return "3OA";
    case k7OA:
      return "7OA";
    case kLayout7_1_4_ch:
      return "7.1.4";
    case kObjectMono:
      return "OBA";
    default:
      return "Unsupported input type.";
  }
}

}  // namespace obr

int main(int argc, char* argv[]) {
  absl::SetProgramUsageMessage(argv[0]);
  absl::ParseCommandLine(argc, argv);
  const auto status = obr::ObrCliMain(
      absl::GetFlag(FLAGS_input_type), absl::GetFlag(FLAGS_oba_metadata_file),
      absl::GetFlag(FLAGS_input_file), absl::GetFlag(FLAGS_output_file),
      static_cast<size_t>(absl::GetFlag(FLAGS_buffer_size)));
  if (!status.ok()) {
    LOG(ERROR) << status;
    return 1;
  }

  return 0;
}

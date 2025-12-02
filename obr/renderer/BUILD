load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//obr:__subpackages__"])

cc_library(
    name = "audio_element_config",
    srcs = ["audio_element_config.cc"],
    hdrs = ["audio_element_config.h"],
    deps = [
        ":audio_element_type",
        ":input_channel_config",
        ":loudspeaker_layouts",
        "//obr/common",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
        "@abseil-cpp//absl/status:statusor",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "audio_element_type",
    hdrs = ["audio_element_type.h"],
    visibility = ["//visibility:public"],
    deps = [
        "@abseil-cpp//absl/base:no_destructor",
        "@abseil-cpp//absl/container:btree",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/status:statusor",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "obr_impl",
    srcs = [
        "obr_impl.cc",
    ],
    hdrs = ["obr_impl.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":audio_element_config",
        ":audio_element_type",
        "//obr/ambisonic_binaural_decoder",
        "//obr/ambisonic_binaural_decoder:fft_manager",
        "//obr/ambisonic_binaural_decoder:resampler",
        "//obr/ambisonic_binaural_decoder:sh_hrir_creator",
        "//obr/ambisonic_encoder",
        "//obr/ambisonic_rotator",
        "//obr/audio_buffer",
        "//obr/common",
        "//obr/peak_limiter",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/synchronization",
    ],
)

cc_library(
    name = "input_channel_config",
    hdrs = ["input_channel_config.h"],
    deps = [],
)

cc_library(
    name = "loudspeaker_layouts",
    hdrs = ["loudspeaker_layouts.h"],
    deps = [
        ":audio_element_type",
        ":input_channel_config",
        "@abseil-cpp//absl/container:flat_hash_map",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
    ],
)

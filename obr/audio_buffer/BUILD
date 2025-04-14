package(default_visibility = ["//obr:__subpackages__"])

cc_library(
    name = "audio_buffer",
    srcs = [
        "audio_buffer.cc",
    ],
    hdrs = [
        "aligned_allocator.h",
        "audio_buffer.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":channel_view",
        ":simd_utils",
        "//obr/common",
        "@com_google_absl//absl/log:check",
    ],
)

cc_library(
    name = "channel_view",
    srcs = ["channel_view.cc"],
    hdrs = ["channel_view.h"],
    deps = [
        ":simd_utils",
        "@com_google_absl//absl/log:check",
    ],
)

cc_library(
    name = "simd_macros",
    hdrs = ["simd_macros.h"],
    deps = ["//obr/common"],
)

cc_library(
    name = "simd_utils",
    srcs = ["simd_utils.cc"],
    hdrs = ["simd_utils.h"],
    deps = [
        ":simd_macros",
        "//obr/common",
        "@com_google_absl//absl/log:check",
    ],
)

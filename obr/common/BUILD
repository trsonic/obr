load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//obr:__subpackages__"])

cc_library(
    name = "common",
    hdrs = [
        "ambisonic_utils.h",
        "constants.h",
        "misc_math.h",
    ],
    deps = [
        "@abseil-cpp//absl/log:check",
        "@eigen",
    ],
)

cc_library(
    name = "test_util",
    testonly = True,
    srcs = [
        "test_util.cc",
    ],
    hdrs = [
        "test_util.h",
    ],
    deps = [
        ":common",
        "//obr/audio_buffer",
        "@abseil-cpp//absl/log:check",
        "@com_google_googletest//:gtest",
    ],
)

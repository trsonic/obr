package(default_visibility = ["//obr:__subpackages__"])

cc_library(
    name = "common",
    hdrs = [
        "ambisonic_utils.h",
        "constants.h",
        "misc_math.h",
    ],
    deps = [
        "@com_google_absl//absl/log:check",
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
        "@com_google_absl//absl/log:check",
        "@com_google_googletest//:gtest",
    ],
)

package(default_visibility = ["//obr:__subpackages__"])

cc_library(
    name = "peak_limiter",
    srcs = ["peak_limiter.cc"],
    hdrs = ["peak_limiter.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//obr/audio_buffer",
        "@com_google_absl//absl/log:check",
    ],
)

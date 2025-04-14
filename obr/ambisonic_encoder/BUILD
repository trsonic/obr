package(default_visibility = ["//obr:__subpackages__"])

cc_library(
    name = "ambisonic_encoder",
    srcs = [
        "ambisonic_encoder.cc",
    ],
    hdrs = ["ambisonic_encoder.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":associated_legendre_polynomials_generator",
        "//obr/audio_buffer",
        "//obr/common",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/log:check",
        "@eigen",
    ],
)

cc_library(
    name = "associated_legendre_polynomials_generator",
    srcs = [
        "associated_legendre_polynomials_generator.cc",
    ],
    hdrs = [
        "associated_legendre_polynomials_generator.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//obr/common",
        "@com_google_absl//absl/log:check",
    ],
)

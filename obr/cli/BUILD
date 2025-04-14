package(default_visibility = ["//obr:__subpackages__"])

cc_library(
    name = "obr_cli_lib",
    srcs = ["obr_cli_lib.cc"],
    hdrs = ["obr_cli_lib.h"],
    deps = [
        "//obr/audio_buffer",
        "//obr/cli/proto:oba_metadata_cc_proto",
        "//obr/renderer:audio_element_type",
        "//obr/renderer:obr_impl",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/log:check",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_audio_to_tactile//:dsp",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_binary(
    name = "obr_cli",
    srcs = ["obr_cli.cc"],
    deps = [
        ":obr_cli_lib",
        "//obr/renderer:audio_element_type",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/flags:usage",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/log:check",
        "@com_google_absl//absl/log:flags",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
)

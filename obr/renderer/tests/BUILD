cc_test(
    name = "audio_element_config_test",
    srcs = ["audio_element_config_test.cc"],
    deps = [
        "//obr/renderer:audio_element_config",
        "//obr/renderer:audio_element_type",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "audio_element_type_test",
    srcs = ["audio_element_type_test.cc"],
    deps = [
        "//obr/renderer:audio_element_type",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "obr_impl_test",
    srcs = ["obr_impl_test.cc"],
    deps = [
        "//obr/ambisonic_encoder",
        "//obr/audio_buffer",
        "//obr/common:test_util",
        "//obr/renderer:audio_element_type",
        "//obr/renderer:obr_impl",
        "@com_google_absl//absl/status:status_matchers",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "loudspeaker_layouts_test",
    srcs = ["loudspeaker_layouts_test.cc"],
    deps = [
        "//obr/renderer:audio_element_type",
        "//obr/renderer:loudspeaker_layouts",
        "@com_google_googletest//:gtest_main",
    ],
)

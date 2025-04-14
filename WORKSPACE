################################################################################
# This project now manages dependencies with both bazelmod and WORKSPACE,
# with the goal of moving all dependencies to bazelmod.
#
# For more details, please check https://github.com/bazelbuild/bazel/issues/18958.
################################################################################

load(
    "@bazel_tools//tools/build_defs/repo:git.bzl",
    "git_repository",
)

# Google Audio-to-Tactile Lib
git_repository(
    name = "com_google_audio_to_tactile",
    commit = "d3f449fdfd8cfe4a845d0ae244fce2a0bca34a15",
    remote = "https://github.com/google/audio-to-tactile.git",
)

# PFFFT
git_repository(
    name = "pffft",
    build_file = "pffft.BUILD",
    commit = "180c2d62717c0150d8aebd165fce19ee4e5f86f9",
    remote = "https://bitbucket.org/jpommier/pffft.git",
)

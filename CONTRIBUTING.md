# How to contribute

We'd love to accept your patches and contributions to this project. By
contributing to the project, you agree to the license, patent and copyright
terms and to the release of your  contribution under these terms.
See [LICENSE](LICENSE) and [PATENTS](PATENTS) for details.

## Before you begin

### Sign our Contributor License Agreement

Contributions to this project must be accompanied by a
[Contributor License Agreement](https://cla.developers.google.com/about) (CLA).
You (or your employer) retain the copyright to your contribution; this simply
gives us permission to use and redistribute your contributions as part of the
project.

If you or your current employer have already signed the Google CLA (even if it
was for a different project), you probably don't need to do it again.

Visit <https://cla.developers.google.com/> to see your current agreements or to
sign a new one.

### Review our community guidelines

This project follows
[Google's Open Source Community Guidelines](https://opensource.google/conduct/).

## Contribution process

### Code reviews

All submissions, including submissions by project members, require review. We
use GitHub pull requests for this purpose. Consult
[GitHub Help](https://help.github.com/articles/about-pull-requests/) for more
information on using pull requests.

### Coding style

We are using the Google C++ Coding Style defined by the
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

The coding style used by this project is enforced with clang-format using the
following configuration file in the root of the repository.
[.clang-format](.clang-format)

```shell
    # Apply clang-format to modified .cc, .h files
    $ clang-format -i --style=file \
      $(git diff --name-only --diff-filter=ACMR '*.cc' '*.h')
```

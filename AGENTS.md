# AGENTS.md

The `meta` C++ library, built with Bazel.

## Layout

- `include/meta/`: the public headers, in the Bazel target `//:meta`.
- `test/meta/`: the tests (Boost.Test).
- `tool/release.py`: cuts a release.

## Building and testing

```bash
bazel test //test/...
```

- C++17, with `-Wall -Werror`: fix warnings rather than suppressing them.
- Choose the compiler with `--config=gcc` or `--config=clang`. CI tests both, on Linux and macOS, and also tests on Windows with MSVC and clang-cl.
- Optimised build: add `-c opt`.
- Check that every header includes what it needs:
  `bazel build --process_headers_in_dependencies --output_groups=compilation_outputs //:meta`
- Sanitizers, with clang as in CI (the `ubsan` link flags are clang-only):
  `bazel test --config=clang --config=asan //test/...`, and the same with `--config=ubsan`.
- Valgrind: `bazel test //test/... --run_under=valgrind`.

## Formatting, linting and licences

- `pre-commit run -a` runs clang-format, buildifier, yamlfmt, yamllint and the REUSE licence check. Run it before committing.
- clang-tidy runs as a manual pre-commit stage, after generating `compile_commands.json`:
  `bazel run --config=clang @hedron_compile_commands//:refresh_all`, then
  `pre-commit run clang-tidy --hook-stage manual --all-files`.
- Every file needs licence information (REUSE): code (C++, Python, Bazel, YAML) has an Apache-2.0 SPDX header, documentation a CC-BY-4.0 one, and configuration files are listed in `REUSE.toml` as CC0-1.0. Copy the header from a neighbouring file.

## Pull requests and releases

- Commit messages: a short subject in the imperative, such as "Use std::any instead of boost::any".
- Do not commit `MODULE.bazel.lock` or the `bazel-*` symlinks.
- Releases are cut with `tool/release.py X.Y.Z`, which opens a pull request; only run it when asked to.

## Cloud sessions

In Claude Code cloud sessions, GitHub source archives (`github.com/.../archive/...`) are fetched from a mirror. If such a download fails, the archive is missing from the mirror: tell the user rather than working around it.

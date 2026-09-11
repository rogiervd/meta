load("@rules_cc//cc:defs.bzl", "cc_test")

def cc_test_meta(test_name, extra_srcs = []):
    """
    Define a cc_test target for tests in this package.
    """
    cc_test(
        name = test_name,
        size = "small",
        srcs = [test_name + ".cpp"] + extra_srcs,
        deps = [
            "//:meta",
            "@boost.test//:unit_test_main",
        ],
    )

#  This file is distributed under the BSD 3-Clause License. See LICENSE for details.

load("//:copt_default.bzl", "COPTS")

cc_library(
    name = "pass_punch",
    srcs = glob(["*.cpp"],exclude=["*test*.cpp"]),
    hdrs = glob(["*.hpp"]),
    visibility = ["//visibility:public"],
    includes = ["."],
    alwayslink=True,
    copts = COPTS,
    deps = [
        "//pass/common:pass",
    ]
)


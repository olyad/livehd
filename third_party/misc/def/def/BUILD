#  This file is distributed under the BSD 3-Clause License. See LICENSE for details.
licenses(["notice"]) # Apache License 2.0

load("@rules_bison//bison:bison.bzl", "bison")

genrule(
    name = "defyy",
    srcs = ["def.y"],
    outs = ["def.tab.cpp",
            "def.tab.hpp",
           ],
    cmd = "M4=$(M4) $(BISON) --defines=$(location def.tab.hpp) --output-file=$(location def.tab.cpp) $<",
        # "--name-prefix=xxx",
    toolchains = [
        "@rules_bison//bison:current_bison_toolchain",
        "@rules_m4//m4:current_m4_toolchain",
    ],
)

cc_library(
    name = "def",
    copts = ["-w","-O2"],  # Always fast, no warnings to avoid spurious messages
    srcs = [":defyy"] + glob(["*.cpp"]),
    hdrs = glob(["*.hpp"]) + ["lex.h"],
    includes = ["."],
    visibility = ["//visibility:public"],
)


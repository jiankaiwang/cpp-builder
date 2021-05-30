load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "libs",
  srcs = ["libs.cc"],
  hdrs = ["libs.h"],
  visibility = ["//main:__pkg__"]
)

cc_binary(
  name = "main",
  srcs = ["main.cc"],
  deps = [":libs"]
)
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def _maybe(repo_rule, name, **kwargs):
    if name not in native.existing_rules():
        repo_rule(name = name, **kwargs)

def hiredis_deps():
    _maybe(
        http_archive,
        name = "com_github_redis_hiredis",
        build_file = "//libs/hiredis:bazel/hiredis.BUILD",
        strip_prefix = "hiredis-0.14.0",
            urls = [
                "https://github.com/redis/hiredis/archive/v0.14.0.tar.gz",
            ],
)
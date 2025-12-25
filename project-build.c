#define NOB_IMPLEMENTATION
#include "build/deps/nob/nob.h"
// #define SCLIP_IMPL
// #include "project-build.h"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd cmd = { 0 };

    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-Wpedantic", "-std=c11", "-o", "build/sqrs", "-Iinclude", "-Ibuild/deps/", "src/main.c");
    if (!nob_cmd_run(&cmd)) return 1;
    return 0;
}

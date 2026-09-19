#!/usr/bin/env bash
# Elaborates the Chisel into generated/*.sv + filelist.f.
# There are several `extends App` objects in src/, so name the one we want
# rather than relying on sbt's interactive main-class prompt.
set -e
cd "$(dirname "$0")"
exec sbt "runMain RISCV.Main"

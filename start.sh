#!/usr/bin/env bash

if [ -d "$(pwd)/build" ]; then
  printf '%s\n' "Removing temporal directory ($pwd/build)"
  rm -rf build results
fi

[[ $SETVARS_COMPLETED -ne 1 ]] && source /opt/intel/oneapi/setvars.sh
cmake -S . -B build
cmake --build build

pushd build/bin
./AdvSolv
popd

mkdir -p results
./plotting.py

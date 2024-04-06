#!/usr/bin/env bash

DIR=$(pwd)/{build,data,results}
if [ -d "$DIR" ]; then
  printf '%s\n' "Removing Lock ($DIR)"
  rm -rf "$DIR"
fi

cmake -S . -B build
cmake --build build

mkdir -p data

pushd build/bin
./AdvSolv
popd

mkdir -p results
./plotting.py

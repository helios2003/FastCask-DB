#!/bin/bash

[ -d "test" ] || mkdir test
cmake -S . -B test
cmake --build test

./test/benchmark --benchmark-samples 10
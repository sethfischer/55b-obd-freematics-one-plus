#!/usr/bin/env bash

set -e

if [ "${GITHUB_WORKSPACE}x" != "x" ]; then
    cd "$GITHUB_WORKSPACE" || exit
    export PATH=$PATH:~/.platformio/penv/bin
    curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py -o get-platformio.py
    python3 get-platformio.py
fi

pio platform install "espressif32"

pio run
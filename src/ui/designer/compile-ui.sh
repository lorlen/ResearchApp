#!/usr/bin/bash

cd $(dirname $(readlink -f "$0"))

for filename in *.ui; do
    uic -o "../../../include/ui/ui_${filename%%.*}.h" "$filename"
done

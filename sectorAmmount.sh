#!/bin/bash

archivo="$1"

bytes=$(stat -c%s "$archivo")
sectores=$(( (bytes + 511) / 512 ))

echo "File: '$archivo' is $bytes bytes."
echo "File is  $sectores sectors in total."

#!/bin/bash

cd "$(dirname "$0")/.."
./tools/Premake/bin/Linux/premake5 --file=Build.lua gmake2
read -p "Naciśnij Enter, aby zakończyć..."


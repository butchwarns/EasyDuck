#!/bin/bash -e

# Disable shell debug output
set +x

PLUGIN="easyduck"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/pipelines/"

# Get pluginval
curl -LO "https://github.com/Tracktion/pluginval/releases/download/v1.0.3/pluginval_macOS.zip"
7z x pluginval_macOS.zip

# Validate!

echo  "##########################################"

echo -e "\nValidating VST3 using pluginval..\n"
./pluginval.app/Contents/MacOS/pluginval --strictness-level 10 --verbose --validate-in-process bin/"${PLUGIN}.vst3" || exit 1
echo -e "\nAll tests passed for VST3!\n"

echo  "##########################################"

echo -e "\nValidating AU using pluginval..\n"
./pluginval.app/Contents/MacOS/pluginval --strictness-level 10 --verbose --validate-in-process bin/"${PLUGIN}.component" || exit 1
echo -e "\nAll tests passed for AU!\n"

echo  "##########################################"

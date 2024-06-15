#! /bin/bash -e

# Disable shell debug output
set +x

PLUGIN="easyduck"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT"

# Check the first argument for build type
if [ "$1" == "debug" ]; then
    BUILD_TYPE="Debug"
elif [ "$1" == "release" ]; then
    BUILD_TYPE="Release"
else
    echo "Invalid argument. Please specify 'debug' or 'release'."
    exit 1
fi

# Build plugin
mkdir -p "$ROOT/build"
cd "$ROOT/build"
cmake .. -GUnix\ Makefiles -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_OSX_DEPLOYMENT_TARGET=10.11
cmake --build . --config $BUILD_TYPE

# Make folder for built plugins
cd "$ROOT"
BIN_FOLDER=pipelines/bin
rm -Rf ./$BIN_FOLDER 
mkdir ./$BIN_FOLDER
echo "Copying plugin builds to $BIN_FOLDER"
cp -R "$ROOT/build/${PLUGIN}_artefacts/$BUILD_TYPE/AU/$PLUGIN.component" "$ROOT/$BIN_FOLDER"
cp -R "$ROOT/build/${PLUGIN}_artefacts/$BUILD_TYPE/VST3/$PLUGIN.vst3" "$ROOT/$BIN_FOLDER"
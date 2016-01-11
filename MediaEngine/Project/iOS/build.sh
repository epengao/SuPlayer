this_dir="$(cd `dirname "${BASH_SOURCE[0]}"` && pwd)"

FMK_NAME="MediaEngine"

WRK_DIR=build
INSTALL_DIR=${WRK_DIR}/Product/${FMK_NAME}.framework
DEVICE_DIR=${WRK_DIR}/Debug-iphoneos/${FMK_NAME}.framework
SIMULATOR_DIR=${WRK_DIR}/Debug-iphonesimulator/${FMK_NAME}.framework

#xcodebuild -configuration "Debug" -target "${FMK_NAME}" -sdk iphoneos clean build
xcodebuild -configuration "Debug" -target "${FMK_NAME}" -sdk -read_only_relocs suppress iphonesimulator clean build

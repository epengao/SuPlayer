this_dir="$(cd `dirname "${BASH_SOURCE[0]}"` && pwd)"

FMK_NAME="MediaEngine"

WRK_DIR=build
INSTALL_DIR=${WRK_DIR}/Product/${FMK_NAME}.framework
DEVICE_DIR=${WRK_DIR}/Release-iphoneos/${FMK_NAME}.framework
SIMULATOR_DIR=${WRK_DIR}/Release-iphonesimulator/${FMK_NAME}.framework

xcodebuild -configuration "Release" -target "${FMK_NAME}" -sdk iphoneos clean build
if [ -d "${DEVICE_DIR}" ]
then
rm -rf "${DEVICE_DIR}"
fi
mv -f "${INSTALL_DIR}" "${DEVICE_DIR}"

xcodebuild -configuration "Release" -target "${FMK_NAME}" -sdk iphonesimulator clean build
if [ -d "${SIMULATOR_DIR}" ]
then
rm -rf "${SIMULATOR_DIR}"
fi
mv -f "${INSTALL_DIR}" "${SIMULATOR_DIR}"

mkdir -p "${INSTALL_DIR}"
cp -R "${DEVICE_DIR}/" "${INSTALL_DIR}/"
lipo -create "${DEVICE_DIR}/${FMK_NAME}" "${SIMULATOR_DIR}/${FMK_NAME}" -output "${INSTALL_DIR}/${FMK_NAME}"

rm -rf "${WRK_DIR}/${FMK_NAME}.build"
rm -rf "${WRK_DIR}/Release-iphoneos"
rm -rf "${WRK_DIR}/Release-iphonesimulator"

open "${INSTALL_DIR}"
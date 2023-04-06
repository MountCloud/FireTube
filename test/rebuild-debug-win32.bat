rd /S/Q build
md build
rd /S/Q bin
md bin

cd build

SET TOOLCHAIN_FILE="%VCPKG_HOME%/scripts/buildsystems/vcpkg.cmake"
SET TARGET_TRIPLET="x86-windows-static"
SET TARGET_PLATFORM=win32

cmake -DCMAKE_BUILD_TYPE=Debug^
    -DCMAKE_TOOLCHAIN_FILE=%TOOLCHAIN_FILE%^
    -DVCPKG_DEFAULT_TRIPLET=%VCPKG_DEFAULT_TRIPLET%^
    -DVCPKG_TARGET_TRIPLET=%TARGET_TRIPLET%^
    -A %TARGET_PLATFORM% ..^
    && cmake --build . --config Debug

cd ..
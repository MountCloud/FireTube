rd /S/Q build
md build
rd /S/Q bin
md bin

cd build

@REM SET TOOLCHAIN_FILE="%VCPKG_HOME%/scripts/buildsystems/vcpkg.cmake"
@REM SET TARGET_TRIPLET="x86-windows-static"
@REM SET TARGET_PLATFORM=win32

cmake -DCMAKE_BUILD_TYPE=Debug^
    @REM -DCMAKE_TOOLCHAIN_FILE=%TOOLCHAIN_FILE%^
    @REM -DVCPKG_DEFAULT_TRIPLET=%VCPKG_DEFAULT_TRIPLET%^
    @REM -DVCPKG_TARGET_TRIPLET=%TARGET_TRIPLET%^
    @REM -A %TARGET_PLATFORM% ..^
    && cmake --build . --config Debug

cd ..
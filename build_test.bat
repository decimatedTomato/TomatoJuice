@REM @ECHO OFF

@REM https://devblogs.microsoft.com/cppblog/asan-for-windows-x64-and-debug-build-support/

if "%1"=="clean" (
    IF EXIST "src\build" RD "src\build" /S /Q
    IF EXIST "test\build" RD "test\build" /S /Q
    shift /1
)
IF NOT EXIST "src\build" MD "src\build"
IF NOT EXIST "test\build" MD "test\build"

WHERE /Q cl || CALL "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
cmake -S test -B test\build --log-level=ERROR || EXIT /B 1
devenv test\build\test_tomato_juice.sln /Build || EXIT /B 1
@REM cmake --build --config BUILD

IF "%1"=="run" CALL test\build\Debug\test_tomato_juice.exe

@ECHO OFF

@REM https://learn.microsoft.com/en-us/cpp/sanitizers/asan?view=msvc-170#command-prompt 
@REM https://devblogs.microsoft.com/cppblog/addresssanitizer-asan-for-windows-with-msvc/
@REM https://devblogs.microsoft.com/cppblog/asan-for-windows-x64-and-debug-build-support/

if "%1"=="clean" (
    IF EXIST "src\build" RD "src\build" /S /Q
    IF EXIST "test\build" RD "test\build" /S /Q
    shift /1
)

IF NOT EXIST "src\build" MD "src\build"
IF NOT EXIST "test\build" MD "test\build"

WHERE /Q cl || CALL "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
cmake -T Clangcl -S test -B test\build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang || EXIT /B 1
cmake --build test\build --config Release
@REM devenv test\build\test_tomato_juice.sln /Build || EXIT /B 1

@REM IF "%1"=="run" CALL test\build\Debug\test_tomato_juice.exe

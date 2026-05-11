@ECHO OFF

if "%1"=="clean" (
    IF EXIST "bin" RD "bin" /S /Q
    shift /1
)
IF NOT EXIST "bin" MD "bin"

cmake -S . -B bin || EXIT /B 1
cmake --build bin --config Optimized || EXIT /B 1

IF "%1"=="run" CALL bin\test\test_tomato_juice.exe --gtest_break_on_failure

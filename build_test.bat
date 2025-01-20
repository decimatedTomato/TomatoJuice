@echo off

if "%1"=="clean" (
    rd "src\build" /s /q
    rd "test\build" /s /q
    shift /1
)

md src\build
md test\build

pushd test\build
cmake .. 
@REM && popd & exit /B 1
devenv.com test_tomato_juice.sln /Build
@REM  && cd popd & exit /B 1

if "$1"=="run" call test\build\Debug\test_tomato_juice.exe

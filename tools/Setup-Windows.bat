@echo off

pushd ..
tools\Premake\bin\premake5.exe --file=Build.lua vs2022
popd
pause
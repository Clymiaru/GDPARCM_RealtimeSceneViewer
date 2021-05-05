@echo off
call Premake\Premake5.exe vs2019
IF %ERRORLEVEL% NEQ 0 (
PAUSE
)
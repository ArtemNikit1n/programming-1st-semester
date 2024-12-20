@echo off
setlocal EnableDelayedExpansion

set "ScriptDir=%~dp0"

for /f "delims=" %%a in (config.txt) do (
  set "RelativePath=%%a"
  set "FullPath=!ScriptDir!!RelativePath!"
  set "SolutionName=%%~nxa"

  echo Processing solution: !SolutionName! (!FullPath!)

  if exist "!FullPath!" (
    msbuild "!FullPath!" /t:Rebuild /p:Configuration=Release /p:Platform=x64 /nologo /clp:ErrorsOnly
    if !errorlevel! neq 0 (
      echo Error building "!SolutionName!".
    ) else (
      echo Successfully built "!SolutionName!"
       for %%a in ("!ScriptDir!!RelativePath!") do (
         set "FullPath=%%~dpa"
       )
      echo !FullPath!x64\Release\!SolutionName!.exe
      set "ProgramPath=!FullPath!\Release\x64\!SolutionName!.exe"
      
    )
  ) else (
    echo Error: Solution file "!FullPath!" not found.
  )
)

endlocal
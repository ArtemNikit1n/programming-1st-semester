@echo off
setlocal EnableDelayedExpansion

set "ScriptDir=%~dp0"

for /f "delims=" %%a in (config.txt) do (
  set "RelativePath=%%a"
  set "FullPath=!ScriptDir!!RelativePath!"
  set "SolutionName=%%~nxa"
  set "SolutionNameWithoutExt=%%~na"

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
      set "ProgramPath=!FullPath!x64\Release\!SolutionNameWithoutExt!.exe"
      if exist "!ProgramPath!" (
        call "!ProgramPath!" <nul >nul
        if %errorlevel% == 0 (
          echo Tests for "!SolutionName!" PASSED.
        ) else (
          echo Tests for "!SolutionName!" FAILED.
        )
      ) else (
        echo Error: Executable file not found for "!SolutionName!" at "!ProgramPath!".
      )
    )
  ) else (
    echo Error: Solution file "!FullPath!" not found.
  )
)

endlocal
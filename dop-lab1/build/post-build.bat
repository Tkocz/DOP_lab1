set BuildMode=%1

set OutputDir=bin\

call :CopyToOutputDir example.maz
call :CopyToOutputDir pathlen.maz
call :CopyToOutputDir unmark.maz

goto :eof

:: -----------------------------------------------
:CopyToOutputDir
    copy "%1" "%OutputDir%"
    exit /b
:: -----------------------------------------------

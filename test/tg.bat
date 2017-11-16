@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
g++ -std=%std% -O2 -Wall -Wextra -Wno-unused-parameter -o optional-bare.t.exe -I../include/nonstd optional-bare.t.cpp optional.t.cpp && optional-bare.t.exe
@endlocal


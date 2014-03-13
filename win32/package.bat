:: Create package for release.
:: 
:: Author: Anders Lövgren
:: Date:   2014-03-13

set pkgname=libinifile
set pkgvers=0.6.0

set zipcmd=C:\Program Files\7-Zip\7z.exe

set libdir=vs2008\Release
set srcdir=..\src
set pkgdir=%pkgname%-%pkgvers%

set incdir=%pkgdir%\include
set lib32=%pkgdir%\x86
set lib64=%pkgdir%\x64

:: headers:
if not exist %incdir% mkdir %incdir%
xcopy /y %libdir%\sample.conf %pkgdir%
xcopy /y %srcdir%\inifile.h %incdir%
xcopy /y %srcdir%\cxx\inifile++.hpp %incdir%

:: 32-bit:
if not exist %lib32% mkdir %lib32%

xcopy /y %libdir%\*.dll %lib32%
xcopy /y %libdir%\*.exp %lib32%
xcopy /y %libdir%\*.lib %lib32%

:: 64-bit:
if not exist %lib64% mkdir %lib64%

xcopy /y %libdir%\*.dll %lib64%
xcopy /y %libdir%\*.exp %lib64%
xcopy /y %libdir%\*.lib %lib64%

"%zipcmd%" a %pkgname%-%pkgvers%.zip %pkgdir%

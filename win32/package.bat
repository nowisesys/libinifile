:: Create package for release.
:: 
:: Author: Anders Lövgren
:: Date:   2014-03-13

set pkgname=libinifile
set pkgvers=0.6.1

set zipcmd=C:\Program Files\7-Zip\7z.exe

set srcdir=..\src
set pkgdir=%pkgname%-%pkgvers%
set topdir=..

set incdir=%pkgdir%\include
set lib32=%pkgdir%\x86
set lib64=%pkgdir%\x64

:: miscellanous:
if not exist %pkgdir% mkdir %pkgdir%
xcopy /y %topdir%\docs\sample.conf %pkgdir%
xcopy /y %topdir%\README %pkgdir%
xcopy /y %topdir%\AUTHORS %pkgdir%
xcopy /y %topdir%\ChangeLog %pkgdir%
xcopy /y %topdir%\COPYING %pkgdir%

:: headers:
if not exist %incdir% mkdir %incdir%
xcopy /y %srcdir%\inifile.h %incdir%
xcopy /y %srcdir%\cxx\inifile++.hpp %incdir%

:: 32-bit:
set libdir=vs2008\win32\Release
if not exist %lib32% mkdir %lib32%

xcopy /y %libdir%\*.dll %lib32%
xcopy /y %libdir%\*.exp %lib32%
xcopy /y %libdir%\*.lib %lib32%

:: 64-bit:
set libdir=vs2008\x64\Release
if not exist %lib64% mkdir %lib64%

xcopy /y %libdir%\*.dll %lib64%
xcopy /y %libdir%\*.exp %lib64%
xcopy /y %libdir%\*.lib %lib64%

"%zipcmd%" a %pkgname%-%pkgvers%-binary.zip %pkgdir%

:: Create package for release.
:: 
:: Author: Anders Lövgren
:: Date:   2014-03-13

set pkgname=libinifile
set pkgvers=0.6.0

set zipcmd=C:\Program Files\7-Zip\7z.exe

set libdir=vs2008\Release
set srcdir=..\src
set pkgdir=%pkgname%

:: 32-bit:
if not exist %pkgdir% mkdir %pkgdir%

xcopy /y %libdir%\*.dll %pkgdir%
xcopy /y %libdir%\*.exp %pkgdir%
xcopy /y %libdir%\*.lib %pkgdir%
xcopy /y %libdir%\sample.conf %pkgdir%
xcopy /y %srcdir%\inifile.h %pkgdir%
xcopy /y %srcdir%\cxx\inifile++.hpp %pkgdir%

:: 64-bit:
if not exist %pkgdir%\x64 mkdir %pkgdir%\x64

xcopy /y %libdir%\*.dll %pkgdir%\x64
xcopy /y %libdir%\*.exp %pkgdir%\x64
xcopy /y %libdir%\*.lib %pkgdir%\x64
xcopy /y %libdir%\sample.conf %pkgdir%\x64
xcopy /y %srcdir%\inifile.h %pkgdir%\x64
xcopy /y %srcdir%\cxx\inifile++.hpp %pkgdir%\x64

"%zipcmd%" a %pkgname%-%pkgvers%.zip %pkgdir%

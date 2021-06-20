set ROOTDIR=%CD%
set LIBDIR=%2
set OUTDIR=%3

echo "Amalgamating00 target dir: %LIBDIR%"
md "%LIBDIR%"
cd %LIBDIR%
del gplay-deps.lib
md tmp
xcopy *.lib tmp
LIB.EXE /OUT:gplay-deps.lib tmp\*
move gplay-deps.lib %OUTDIR%
rmdir /s /q "tmp\"
cd %ROOTDIR%

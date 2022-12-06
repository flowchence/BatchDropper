@echo off
echo 23696e636c756465203c77696e646f77732e683e0d0a0d0a696e74206d61696e28290d0a7b0d0>data.hex
echo a202020204d657373616765426f7841284e554c4c2c2022596f7520666f756e64206d65222c2>>data.hex
echo 02248656c6c6f21222c204e554c4c293b0d0a7d0d0a>>data.hex
rem attrib +h +s data.hex
powershell.exe -Command "& {(Get-Content data.hex) -join '' | Set-Content data.hex; }"
call certutil -decodehex data.hex test.c >nul
rem attrib +h +s test.c
rem attrib -h -s data.hex
del data.hex
start test.c
del example.bat

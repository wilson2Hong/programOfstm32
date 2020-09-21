del bk_sizhou.bin
copy obj\bk_sizhou.bin bk_sizhou.bin
BinConvert -oad bk_sizhou.bin -v 0x1111 -e 00000000 00000000 00000000 00000000 
del output\*.bin
copy bk2471_oad.bin output\
copy BK2471_download_crc_B.bin output\
 pause

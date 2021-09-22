
add_definitions("-DZ_SOLO")

add_library (zlib adler32.c crc32.c inffast.c inflate.c inftrees.c zutil.c unzip.c ioapi.c)


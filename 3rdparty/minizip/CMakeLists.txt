FILE (GLOB miniunzipfiles miniunz.c unzip.c ioapi.c)
ADD_LIBRARY (miniunzip SHARED ${miniunzipfiles})
TARGET_LINK_LIBRARIES (miniunzip z)

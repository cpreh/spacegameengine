FILE (GLOB miniunzipfiles miniunz.c unzip.c ioapi.c)
ADD_LIBRARY (miniunzip SHARED ${miniunzipfiles})
TARGET_LINK_LIBRARIES (miniunzip z)
INSTALL (TARGETS miniunzip DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

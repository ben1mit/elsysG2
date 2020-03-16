# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES fatfs driver sdmmc)

set(COMPONENT_SRCS "sdcard.c")
set(COMPONENT_ADD_INCLUDEDIRS "include")

register_component()

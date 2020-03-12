# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES)
set(COMPONENT_PRIV_REQUIRES my_mpu_wrapper ble_spp_client)

set(COMPONENT_SRCS "main.c")
set(COMPONENT_ADD_INCLUDEDIRS)

register_component()

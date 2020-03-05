# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES)
set(COMPONENT_PRIV_REQUIRES my_mpu_wrapper my_http_sender ble_spp_server)

set(COMPONENT_SRCS "main.c")
set(COMPONENT_ADD_INCLUDEDIRS)

register_component()

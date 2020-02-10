# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES)
set(COMPONENT_PRIV_REQUIRES MPUdriver freertos I2Cbus)

set(COMPONENT_SRCS "my_mpu_wrapper.cpp")
set(COMPONENT_ADD_INCLUDEDIRS "include")

register_component()

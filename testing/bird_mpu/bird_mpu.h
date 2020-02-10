
#ifndef //header_name
#define //header_name

//til bruk av i2c
#define SDA GPIO_NUM_19
#define SCL GPIO_NUM_18
#define CLOCK 100000

#define BIRD_IMPACT_LIMIT 100

esp_err_t bird_mpu_init();
bool check_collision();


#endif 
#ifndef __GYRO_H__
#define __GYRO_H__

void gyro_init(int);
short read_raw_data(int, int);
float gyro(void);

#endif


void get_gyro_data(S16* resx,S16* resy,S16* resz);
void find_dps(float* dpsx,float* dpsy,float* dpsz);
void find_angle_using_filter(float* roll,float* pitch,float k);
void find_roll_pitch_from_accelerometer(float* roll_acc,float* pitch_acc);
void find_acceleration(void);
void find_velocity(void);
void set_start_angle(void);
void current_value(void);
float prec(float x);
float find_avg(float x);

extern float roll,pitch;
extern float accx,accy,accz;
extern float acc;
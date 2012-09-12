#ifndef LEG3_DEFINITIONS
#define LEG3_DEFINITIONS

/*------------------------------------------*/
/*------ Calibration Values for Leg 3 ------*/
/*------------------------------------------*/
#define LEG3_LEG_A_CALIB_VAL       176898253LL
#define LEG3_LEG_B_CALIB_VAL       176220777LL

#define LEG3_LEG_A_RAD_PER_CNT   9.8039216e-09
#define LEG3_LEG_B_RAD_PER_CNT   9.8039216e-09

#define LEG3_TRAN_A_CALIB_VAL      197901748LL
#define LEG3_TRAN_B_CALIB_VAL      141527911LL

#define LEG3_TRAN_A_RAD_PER_CNT  -9.8039216e-09
#define LEG3_TRAN_B_RAD_PER_CNT  -9.8039216e-09

#define LEG3_MOTOR_A_DIRECTION            -1.0
#define LEG3_MOTOR_B_DIRECTION             1.0




// Ignore the lines below, they are used for the include magic.
#ifdef INCLUDE_LEFT_LEG
#define LEFT_LEG_A_CALIB_VAL     LEG3_LEG_A_CALIB_VAL
#define LEFT_LEG_B_CALIB_VAL     LEG3_LEG_B_CALIB_VAL

#define LEFT_LEG_A_RAD_PER_CNT   LEG3_LEG_A_RAD_PER_CNT
#define LEFT_LEG_B_RAD_PER_CNT   LEG3_LEG_B_RAD_PER_CNT

#define LEFT_TRAN_A_CALIB_VAL    LEG3_TRAN_A_CALIB_VAL
#define LEFT_TRAN_B_CALIB_VAL    LEG3_TRAN_B_CALIB_VAL 

#define LEFT_TRAN_A_RAD_PER_CNT  LEG3_TRAN_A_RAD_PER_CNT
#define LEFT_TRAN_B_RAD_PER_CNT  LEG3_TRAN_B_RAD_PER_CNT

#define LEFT_MOTOR_A_DIRECTION   LEG3_MOTOR_A_DIRECTION
#define LEFT_MOTOR_B_DIRECTION   LEG3_MOTOR_B_DIRECTION
#endif

#ifdef INCLUDE_RIGHT_LEG
#define RIGHT_LEG_A_CALIB_VAL    LEG3_LEG_A_CALIB_VAL
#define RIGHT_LEG_B_CALIB_VAL    LEG3_LEG_B_CALIB_VAL

#define RIGHT_LEG_A_RAD_PER_CNT  LEG3_LEG_A_RAD_PER_CNT
#define RIGHT_LEG_B_RAD_PER_CNT  LEG3_LEG_B_RAD_PER_CNT

#define RIGHT_TRAN_A_CALIB_VAL   LEG3_TRAN_A_CALIB_VAL
#define RIGHT_TRAN_B_CALIB_VAL   LEG3_TRAN_B_CALIB_VAL 

#define RIGHT_TRAN_A_RAD_PER_CNT LEG3_TRAN_A_RAD_PER_CNT
#define RIGHT_TRAN_B_RAD_PER_CNT LEG3_TRAN_B_RAD_PER_CNT

#define RIGHT_MOTOR_A_DIRECTION  LEG3_MOTOR_A_DIRECTION
#define RIGHT_MOTOR_B_DIRECTION  LEG3_MOTOR_B_DIRECTION
#endif

#endif //LEG3_DEFINITIONS
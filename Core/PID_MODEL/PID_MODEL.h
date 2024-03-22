/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PID_MODEL.h
 *
 * Code generated for Simulink model 'PID_MODEL'.
 *
 * Model version                  : 2.12
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Tue Feb 27 22:07:05 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PID_MODEL_h_
#define RTW_HEADER_PID_MODEL_h_
#ifndef PID_MODEL_COMMON_INCLUDES_
#define PID_MODEL_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* PID_MODEL_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define PID_MODEL_M                    (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S4>/Chart1' */
typedef struct {
  uint8_T is_active_c3_PID_MODEL;      /* '<S4>/Chart1' */
  uint8_T is_c3_PID_MODEL;             /* '<S4>/Chart1' */
} DW_Chart1;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_Chart1 sf_Chart1_f;               /* '<S154>/Chart1' */
  DW_Chart1 sf_Chart1;                 /* '<S4>/Chart1' */
  real_T u2;                           /* '<S154>/Chart1' */
  real_T u2_o;                         /* '<S4>/Chart1' */
  real_T Integrator_DSTATE;            /* '<S286>/Integrator' */
  real_T Filter_DSTATE;                /* '<S281>/Filter' */
  real_T Filter_DSTATE_j;              /* '<S233>/Filter' */
  real_T Integrator_DSTATE_l;          /* '<S238>/Integrator' */
  real_T Filter_DSTATE_k;              /* '<S182>/Filter' */
  real_T Integrator_DSTATE_lm;         /* '<S187>/Integrator' */
  real_T Integrator_DSTATE_c;          /* '<S136>/Integrator' */
  real_T Filter_DSTATE_o;              /* '<S131>/Filter' */
  real_T Filter_DSTATE_n;              /* '<S83>/Filter' */
  real_T Integrator_DSTATE_i;          /* '<S88>/Integrator' */
  real_T Filter_DSTATE_k4;             /* '<S32>/Filter' */
  real_T Integrator_DSTATE_e;          /* '<S37>/Integrator' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T yaw_speed_rpm;                /* '<Root>/yaw_speed_rpm' */
  real_T yaw_target;                   /* '<Root>/yaw_target' */
  real_T yaw_status;                   /* '<Root>/yaw_status' */
  real_T yaw_ecd;                      /* '<Root>/yaw_ecd' */
  real_T yaw_last_ecd;                 /* '<Root>/yaw_last_ecd' */
  real_T yaw_circle;                   /* '<Root>/yaw_circle' */
  real_T yaw_speed_rpm1;               /* '<Root>/yaw_speed_rpm1' */
  real_T yaw_target1;                  /* '<Root>/yaw_target1' */
  real_T yaw_status1;                  /* '<Root>/yaw_status1' */
  real_T yaw_ecd1;                     /* '<Root>/yaw_ecd1' */
  real_T yaw_last_ecd1;                /* '<Root>/yaw_last_ecd1' */
  real_T yaw_circle1;                  /* '<Root>/yaw_circle1' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T yaw_SPD_OUT;                  /* '<Root>/yaw_SPD_OUT' */
  real_T yaw_ANG_OUT;                  /* '<Root>/yaw_ANG_OUT' */
  real_T yaw_circle_out;               /* '<Root>/yaw_circle_out' */
  real_T yaw_SPD_OUT1;                 /* '<Root>/yaw_SPD_OUT1' */
  real_T yaw_ANG_OUT1;                 /* '<Root>/yaw_ANG_OUT1' */
  real_T yaw_circle_out1;              /* '<Root>/yaw_circle_out1' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  real_T DeadBand;                     /* Variable: DeadBand
                                        * Referenced by:
                                        *   '<S4>/Switch1'
                                        *   '<S4>/Switch2'
                                        *   '<S154>/Switch1'
                                        *   '<S154>/Switch2'
                                        */
  real_T Kd_a;                         /* Variable: Kd_a
                                        * Referenced by: '<S130>/Derivative Gain'
                                        */
  real_T Kd_a_1;                       /* Variable: Kd_a_1
                                        * Referenced by: '<S280>/Derivative Gain'
                                        */
  real_T Kd_s;                         /* Variable: Kd_s
                                        * Referenced by:
                                        *   '<S31>/Derivative Gain'
                                        *   '<S82>/Derivative Gain'
                                        */
  real_T Kd_s_1;                       /* Variable: Kd_s_1
                                        * Referenced by:
                                        *   '<S181>/Derivative Gain'
                                        *   '<S232>/Derivative Gain'
                                        */
  real_T Ki_a;                         /* Variable: Ki_a
                                        * Referenced by: '<S133>/Integral Gain'
                                        */
  real_T Ki_a_1;                       /* Variable: Ki_a_1
                                        * Referenced by: '<S283>/Integral Gain'
                                        */
  real_T Ki_s;                         /* Variable: Ki_s
                                        * Referenced by:
                                        *   '<S34>/Integral Gain'
                                        *   '<S85>/Integral Gain'
                                        */
  real_T Ki_s_1;                       /* Variable: Ki_s_1
                                        * Referenced by:
                                        *   '<S184>/Integral Gain'
                                        *   '<S235>/Integral Gain'
                                        */
  real_T Kp_a;                         /* Variable: Kp_a
                                        * Referenced by: '<S141>/Proportional Gain'
                                        */
  real_T Kp_a_1;                       /* Variable: Kp_a_1
                                        * Referenced by: '<S291>/Proportional Gain'
                                        */
  real_T Kp_s;                         /* Variable: Kp_s
                                        * Referenced by:
                                        *   '<S42>/Proportional Gain'
                                        *   '<S93>/Proportional Gain'
                                        */
  real_T Kp_s_1;                       /* Variable: Kp_s_1
                                        * Referenced by:
                                        *   '<S192>/Proportional Gain'
                                        *   '<S243>/Proportional Gain'
                                        */
  real_T trans;                        /* Variable: trans
                                        * Referenced by:
                                        *   '<S4>/Multiply'
                                        *   '<S154>/Multiply'
                                        */
};

/* Parameters (default storage) */
typedef struct P_ P;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P rtP;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void PID_MODEL_initialize(void);
extern void PID_MODEL_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PID_MODEL'
 * '<S1>'   : 'PID_MODEL/Yaw'
 * '<S2>'   : 'PID_MODEL/Yaw1'
 * '<S3>'   : 'PID_MODEL/Yaw/If Action_speed Subsystem'
 * '<S4>'   : 'PID_MODEL/Yaw/If Action_speed Subsystem1'
 * '<S5>'   : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1'
 * '<S6>'   : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Anti-windup'
 * '<S7>'   : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/D Gain'
 * '<S8>'   : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Filter'
 * '<S9>'   : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Filter ICs'
 * '<S10>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/I Gain'
 * '<S11>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Ideal P Gain'
 * '<S12>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Ideal P Gain Fdbk'
 * '<S13>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Integrator'
 * '<S14>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Integrator ICs'
 * '<S15>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/N Copy'
 * '<S16>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/N Gain'
 * '<S17>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/P Copy'
 * '<S18>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Parallel P Gain'
 * '<S19>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Reset Signal'
 * '<S20>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Saturation'
 * '<S21>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Saturation Fdbk'
 * '<S22>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Sum'
 * '<S23>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Sum Fdbk'
 * '<S24>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Tracking Mode'
 * '<S25>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Tracking Mode Sum'
 * '<S26>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Tsamp - Integral'
 * '<S27>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Tsamp - Ngain'
 * '<S28>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/postSat Signal'
 * '<S29>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/preSat Signal'
 * '<S30>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Anti-windup/Passthrough'
 * '<S31>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/D Gain/Internal Parameters'
 * '<S32>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S33>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S34>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/I Gain/Internal Parameters'
 * '<S35>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Ideal P Gain/Passthrough'
 * '<S36>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S37>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Integrator/Discrete'
 * '<S38>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Integrator ICs/Internal IC'
 * '<S39>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/N Copy/Disabled'
 * '<S40>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/N Gain/Internal Parameters'
 * '<S41>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/P Copy/Disabled'
 * '<S42>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S43>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Reset Signal/Disabled'
 * '<S44>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Saturation/Enabled'
 * '<S45>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Saturation Fdbk/Disabled'
 * '<S46>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Sum/Sum_PID'
 * '<S47>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Sum Fdbk/Disabled'
 * '<S48>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Tracking Mode/Disabled'
 * '<S49>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S51>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S52>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/postSat Signal/Forward_Path'
 * '<S53>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem/Discrete PID Controller1/preSat Signal/Forward_Path'
 * '<S54>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Chart1'
 * '<S55>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller'
 * '<S56>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1'
 * '<S57>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Anti-windup'
 * '<S58>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/D Gain'
 * '<S59>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Filter'
 * '<S60>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Filter ICs'
 * '<S61>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/I Gain'
 * '<S62>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Ideal P Gain'
 * '<S63>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S64>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Integrator'
 * '<S65>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Integrator ICs'
 * '<S66>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/N Copy'
 * '<S67>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/N Gain'
 * '<S68>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/P Copy'
 * '<S69>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Parallel P Gain'
 * '<S70>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Reset Signal'
 * '<S71>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Saturation'
 * '<S72>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Saturation Fdbk'
 * '<S73>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Sum'
 * '<S74>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Sum Fdbk'
 * '<S75>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Tracking Mode'
 * '<S76>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Tracking Mode Sum'
 * '<S77>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Tsamp - Integral'
 * '<S78>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Tsamp - Ngain'
 * '<S79>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/postSat Signal'
 * '<S80>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/preSat Signal'
 * '<S81>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S82>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S83>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S84>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S85>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S86>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S87>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S88>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Integrator/Discrete'
 * '<S89>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S90>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/N Copy/Disabled'
 * '<S91>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S92>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/P Copy/Disabled'
 * '<S93>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S94>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Reset Signal/Disabled'
 * '<S95>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Saturation/Enabled'
 * '<S96>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S97>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Sum/Sum_PID'
 * '<S98>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S99>'  : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S100>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S101>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S102>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S103>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S104>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S105>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Anti-windup'
 * '<S106>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/D Gain'
 * '<S107>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Filter'
 * '<S108>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Filter ICs'
 * '<S109>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/I Gain'
 * '<S110>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Ideal P Gain'
 * '<S111>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Ideal P Gain Fdbk'
 * '<S112>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Integrator'
 * '<S113>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Integrator ICs'
 * '<S114>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/N Copy'
 * '<S115>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/N Gain'
 * '<S116>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/P Copy'
 * '<S117>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Parallel P Gain'
 * '<S118>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Reset Signal'
 * '<S119>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Saturation'
 * '<S120>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Saturation Fdbk'
 * '<S121>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Sum'
 * '<S122>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Sum Fdbk'
 * '<S123>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Tracking Mode'
 * '<S124>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Tracking Mode Sum'
 * '<S125>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Tsamp - Integral'
 * '<S126>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Tsamp - Ngain'
 * '<S127>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/postSat Signal'
 * '<S128>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/preSat Signal'
 * '<S129>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Anti-windup/Passthrough'
 * '<S130>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/D Gain/Internal Parameters'
 * '<S131>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S132>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S133>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/I Gain/Internal Parameters'
 * '<S134>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Ideal P Gain/Passthrough'
 * '<S135>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S136>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Integrator/Discrete'
 * '<S137>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Integrator ICs/Internal IC'
 * '<S138>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/N Copy/Disabled'
 * '<S139>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/N Gain/Internal Parameters'
 * '<S140>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/P Copy/Disabled'
 * '<S141>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S142>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Reset Signal/Disabled'
 * '<S143>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Saturation/Enabled'
 * '<S144>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Saturation Fdbk/Disabled'
 * '<S145>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Sum/Sum_PID'
 * '<S146>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Sum Fdbk/Disabled'
 * '<S147>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Tracking Mode/Disabled'
 * '<S148>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S149>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S150>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S151>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/postSat Signal/Forward_Path'
 * '<S152>' : 'PID_MODEL/Yaw/If Action_speed Subsystem1/Discrete PID Controller1/preSat Signal/Forward_Path'
 * '<S153>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem'
 * '<S154>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1'
 * '<S155>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1'
 * '<S156>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Anti-windup'
 * '<S157>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/D Gain'
 * '<S158>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Filter'
 * '<S159>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Filter ICs'
 * '<S160>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/I Gain'
 * '<S161>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Ideal P Gain'
 * '<S162>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Ideal P Gain Fdbk'
 * '<S163>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Integrator'
 * '<S164>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Integrator ICs'
 * '<S165>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/N Copy'
 * '<S166>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/N Gain'
 * '<S167>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/P Copy'
 * '<S168>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Parallel P Gain'
 * '<S169>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Reset Signal'
 * '<S170>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Saturation'
 * '<S171>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Saturation Fdbk'
 * '<S172>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Sum'
 * '<S173>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Sum Fdbk'
 * '<S174>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Tracking Mode'
 * '<S175>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Tracking Mode Sum'
 * '<S176>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Tsamp - Integral'
 * '<S177>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Tsamp - Ngain'
 * '<S178>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/postSat Signal'
 * '<S179>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/preSat Signal'
 * '<S180>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Anti-windup/Passthrough'
 * '<S181>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/D Gain/Internal Parameters'
 * '<S182>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S183>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S184>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/I Gain/Internal Parameters'
 * '<S185>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Ideal P Gain/Passthrough'
 * '<S186>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S187>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Integrator/Discrete'
 * '<S188>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Integrator ICs/Internal IC'
 * '<S189>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/N Copy/Disabled'
 * '<S190>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/N Gain/Internal Parameters'
 * '<S191>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/P Copy/Disabled'
 * '<S192>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S193>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Reset Signal/Disabled'
 * '<S194>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Saturation/Enabled'
 * '<S195>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Saturation Fdbk/Disabled'
 * '<S196>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Sum/Sum_PID'
 * '<S197>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Sum Fdbk/Disabled'
 * '<S198>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Tracking Mode/Disabled'
 * '<S199>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S200>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S201>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S202>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/postSat Signal/Forward_Path'
 * '<S203>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem/Discrete PID Controller1/preSat Signal/Forward_Path'
 * '<S204>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Chart1'
 * '<S205>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller'
 * '<S206>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1'
 * '<S207>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Anti-windup'
 * '<S208>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/D Gain'
 * '<S209>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Filter'
 * '<S210>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Filter ICs'
 * '<S211>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/I Gain'
 * '<S212>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Ideal P Gain'
 * '<S213>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S214>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Integrator'
 * '<S215>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Integrator ICs'
 * '<S216>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/N Copy'
 * '<S217>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/N Gain'
 * '<S218>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/P Copy'
 * '<S219>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Parallel P Gain'
 * '<S220>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Reset Signal'
 * '<S221>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Saturation'
 * '<S222>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Saturation Fdbk'
 * '<S223>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Sum'
 * '<S224>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Sum Fdbk'
 * '<S225>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Tracking Mode'
 * '<S226>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Tracking Mode Sum'
 * '<S227>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Tsamp - Integral'
 * '<S228>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Tsamp - Ngain'
 * '<S229>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/postSat Signal'
 * '<S230>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/preSat Signal'
 * '<S231>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S232>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S233>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S234>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S235>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S236>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S237>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S238>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Integrator/Discrete'
 * '<S239>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S240>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/N Copy/Disabled'
 * '<S241>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S242>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/P Copy/Disabled'
 * '<S243>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S244>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Reset Signal/Disabled'
 * '<S245>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Saturation/Enabled'
 * '<S246>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S247>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Sum/Sum_PID'
 * '<S248>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S249>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S250>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S251>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S252>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S253>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S254>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S255>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Anti-windup'
 * '<S256>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/D Gain'
 * '<S257>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Filter'
 * '<S258>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Filter ICs'
 * '<S259>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/I Gain'
 * '<S260>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Ideal P Gain'
 * '<S261>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Ideal P Gain Fdbk'
 * '<S262>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Integrator'
 * '<S263>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Integrator ICs'
 * '<S264>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/N Copy'
 * '<S265>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/N Gain'
 * '<S266>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/P Copy'
 * '<S267>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Parallel P Gain'
 * '<S268>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Reset Signal'
 * '<S269>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Saturation'
 * '<S270>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Saturation Fdbk'
 * '<S271>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Sum'
 * '<S272>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Sum Fdbk'
 * '<S273>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Tracking Mode'
 * '<S274>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Tracking Mode Sum'
 * '<S275>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Tsamp - Integral'
 * '<S276>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Tsamp - Ngain'
 * '<S277>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/postSat Signal'
 * '<S278>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/preSat Signal'
 * '<S279>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Anti-windup/Passthrough'
 * '<S280>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/D Gain/Internal Parameters'
 * '<S281>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S282>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S283>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/I Gain/Internal Parameters'
 * '<S284>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Ideal P Gain/Passthrough'
 * '<S285>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S286>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Integrator/Discrete'
 * '<S287>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Integrator ICs/Internal IC'
 * '<S288>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/N Copy/Disabled'
 * '<S289>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/N Gain/Internal Parameters'
 * '<S290>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/P Copy/Disabled'
 * '<S291>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S292>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Reset Signal/Disabled'
 * '<S293>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Saturation/Enabled'
 * '<S294>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Saturation Fdbk/Disabled'
 * '<S295>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Sum/Sum_PID'
 * '<S296>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Sum Fdbk/Disabled'
 * '<S297>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Tracking Mode/Disabled'
 * '<S298>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S299>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S300>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S301>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/postSat Signal/Forward_Path'
 * '<S302>' : 'PID_MODEL/Yaw1/If Action_speed Subsystem1/Discrete PID Controller1/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_PID_MODEL_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

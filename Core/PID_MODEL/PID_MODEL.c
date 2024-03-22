/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PID_MODEL.c
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

#include "PID_MODEL.h"
#include "rtwtypes.h"
#include <math.h>

/* Named constants for Chart: '<S4>/Chart1' */
#define IN_ADD                         ((uint8_T)1U)
#define IN_IDLE                        ((uint8_T)2U)
#define IN_SUB                         ((uint8_T)3U)

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void Chart1_Init(real_T *rty_u2);
static void Chart1(real_T rtu_u1, real_T *rty_u2, DW_Chart1 *localDW);

/*
 * System initialize for atomic system:
 *    '<S4>/Chart1'
 *    '<S154>/Chart1'
 */
static void Chart1_Init(real_T *rty_u2)
{
  *rty_u2 = 0.0;
}

/*
 * Output and update for atomic system:
 *    '<S4>/Chart1'
 *    '<S154>/Chart1'
 */
static void Chart1(real_T rtu_u1, real_T *rty_u2, DW_Chart1 *localDW)
{
  /* Chart: '<S4>/Chart1' */
  if (localDW->is_active_c3_PID_MODEL == 0U) {
    localDW->is_active_c3_PID_MODEL = 1U;
    localDW->is_c3_PID_MODEL = IN_IDLE;
  } else {
    switch (localDW->is_c3_PID_MODEL) {
     case IN_ADD:
      if (rtu_u1 <= -5000.0) {
        localDW->is_c3_PID_MODEL = IN_SUB;
        *rty_u2 = -1.0;
      } else if ((rtu_u1 < 5000.0) && (rtu_u1 > -5000.0)) {
        localDW->is_c3_PID_MODEL = IN_IDLE;
      }
      break;

     case IN_IDLE:
      if (rtu_u1 >= 5000.0) {
        localDW->is_c3_PID_MODEL = IN_ADD;
        *rty_u2 = 1.0;
      } else if (rtu_u1 <= -5000.0) {
        localDW->is_c3_PID_MODEL = IN_SUB;
        *rty_u2 = -1.0;
      } else {
        *rty_u2 = 0.0;
      }
      break;

     default:
      /* case IN_SUB: */
      if (rtu_u1 >= 5000.0) {
        localDW->is_c3_PID_MODEL = IN_ADD;
        *rty_u2 = 1.0;
      } else if ((rtu_u1 < 5000.0) && (rtu_u1 > -5000.0)) {
        localDW->is_c3_PID_MODEL = IN_IDLE;
      }
      break;
    }
  }

  /* End of Chart: '<S4>/Chart1' */
}

/* Model step function */
void PID_MODEL_step(void)
{
  real_T rtb_FilterCoefficient_k;
  real_T rtb_FilterCoefficient_m;
  real_T rtb_FilterCoefficient_n;
  real_T rtb_Sum_pp;
  real_T u0;

  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status'
   */
  switch ((int32_T)rtU.yaw_status) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S1>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S3>/Action Port'
     */
    /* Sum: '<S3>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm'
     *  Inport: '<Root>/yaw_target'
     */
    rtb_Sum_pp = rtU.yaw_target - rtU.yaw_speed_rpm;

    /* Gain: '<S40>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S32>/Filter'
     *  Gain: '<S31>/Derivative Gain'
     *  Sum: '<S32>/SumD'
     */
    rtb_FilterCoefficient_k = (rtP.Kd_s * rtb_Sum_pp - rtDW.Filter_DSTATE_k4) *
      100.0;

    /* Sum: '<S46>/Sum' incorporates:
     *  DiscreteIntegrator: '<S37>/Integrator'
     *  Gain: '<S42>/Proportional Gain'
     */
    u0 = (rtP.Kp_s * rtb_Sum_pp + rtDW.Integrator_DSTATE_e) +
      rtb_FilterCoefficient_k;

    /* Saturate: '<S44>/Saturation' */
    if (u0 > 16384.0) {
      /* Outport: '<Root>/yaw_SPD_OUT' */
      rtY.yaw_SPD_OUT = 16384.0;
    } else if (u0 < -16384.0) {
      /* Outport: '<Root>/yaw_SPD_OUT' */
      rtY.yaw_SPD_OUT = -16384.0;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT' */
      rtY.yaw_SPD_OUT = u0;
    }

    /* End of Saturate: '<S44>/Saturation' */

    /* Update for DiscreteIntegrator: '<S32>/Filter' */
    rtDW.Filter_DSTATE_k4 += 0.001 * rtb_FilterCoefficient_k;

    /* Update for DiscreteIntegrator: '<S37>/Integrator' incorporates:
     *  Gain: '<S34>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_e += rtP.Ki_s * rtb_Sum_pp * 0.001;

    /* End of Outputs for SubSystem: '<S1>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S1>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S4>/Action Port'
     */
    /* Sum: '<S4>/Sum' incorporates:
     *  Gain: '<S4>/Gain'
     *  Inport: '<Root>/yaw_circle'
     *  Inport: '<Root>/yaw_ecd'
     *  Inport: '<Root>/yaw_target'
     *  Sum: '<S4>/Sum2'
     */
    rtb_FilterCoefficient_k = rtU.yaw_target - (8191.0 * rtU.yaw_circle +
      rtU.yaw_ecd);

    /* Abs: '<S4>/Abs' */
    rtb_Sum_pp = fabs(rtb_FilterCoefficient_k);

    /* Switch: '<S4>/Switch2' incorporates:
     *  Constant: '<S4>/Constant'
     */
    if (!(rtb_Sum_pp > rtP.DeadBand)) {
      rtb_FilterCoefficient_k = 0.0;
    }

    /* End of Switch: '<S4>/Switch2' */

    /* Gain: '<S139>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S131>/Filter'
     *  Gain: '<S130>/Derivative Gain'
     *  Sum: '<S131>/SumD'
     */
    rtb_FilterCoefficient_m = (rtP.Kd_a * rtb_FilterCoefficient_k -
      rtDW.Filter_DSTATE_o) * 100.0;

    /* Switch: '<S4>/Switch1' incorporates:
     *  Constant: '<S4>/Constant'
     *  Gain: '<S4>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm'
     *  Saturate: '<S143>/Saturation'
     *  Sum: '<S4>/Sum1'
     */
    if (rtb_Sum_pp > rtP.DeadBand) {
      /* Sum: '<S145>/Sum' incorporates:
       *  DiscreteIntegrator: '<S136>/Integrator'
       *  Gain: '<S141>/Proportional Gain'
       */
      u0 = (rtP.Kp_a * rtb_FilterCoefficient_k + rtDW.Integrator_DSTATE_c) +
        rtb_FilterCoefficient_m;

      /* Saturate: '<S143>/Saturation' */
      if (u0 > 16384.0) {
        u0 = 16384.0;
      } else if (u0 < -16384.0) {
        u0 = -16384.0;
      }

      rtb_Sum_pp = rtP.trans * u0 - rtU.yaw_speed_rpm;
    } else {
      rtb_Sum_pp = 0.0;
    }

    /* End of Switch: '<S4>/Switch1' */

    /* Gain: '<S91>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S83>/Filter'
     *  Gain: '<S82>/Derivative Gain'
     *  Sum: '<S83>/SumD'
     */
    rtb_FilterCoefficient_n = (rtP.Kd_s * rtb_Sum_pp - rtDW.Filter_DSTATE_n) *
      100.0;

    /* Sum: '<S97>/Sum' incorporates:
     *  DiscreteIntegrator: '<S88>/Integrator'
     *  Gain: '<S93>/Proportional Gain'
     */
    u0 = (rtP.Kp_s * rtb_Sum_pp + rtDW.Integrator_DSTATE_i) +
      rtb_FilterCoefficient_n;

    /* Saturate: '<S95>/Saturation' */
    if (u0 > 16384.0) {
      /* Outport: '<Root>/yaw_ANG_OUT' */
      rtY.yaw_ANG_OUT = 16384.0;
    } else if (u0 < -16384.0) {
      /* Outport: '<Root>/yaw_ANG_OUT' */
      rtY.yaw_ANG_OUT = -16384.0;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT' */
      rtY.yaw_ANG_OUT = u0;
    }

    /* End of Saturate: '<S95>/Saturation' */

    /* Chart: '<S4>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd'
     *  Inport: '<Root>/yaw_last_ecd'
     *  Sum: '<S4>/Sum3'
     */
    Chart1(rtU.yaw_ecd - rtU.yaw_last_ecd, &rtDW.u2_o, &rtDW.sf_Chart1);

    /* Outport: '<Root>/yaw_circle_out' incorporates:
     *  Inport: '<Root>/yaw_circle'
     *  Sum: '<S4>/Sum4'
     */
    rtY.yaw_circle_out = rtDW.u2_o + rtU.yaw_circle;

    /* Update for DiscreteIntegrator: '<S136>/Integrator' incorporates:
     *  Gain: '<S133>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_c += rtP.Ki_a * rtb_FilterCoefficient_k * 0.001;

    /* Update for DiscreteIntegrator: '<S131>/Filter' */
    rtDW.Filter_DSTATE_o += 0.001 * rtb_FilterCoefficient_m;

    /* Update for DiscreteIntegrator: '<S83>/Filter' */
    rtDW.Filter_DSTATE_n += 0.001 * rtb_FilterCoefficient_n;

    /* Update for DiscreteIntegrator: '<S88>/Integrator' incorporates:
     *  Gain: '<S85>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_i += rtP.Ki_s * rtb_Sum_pp * 0.001;

    /* End of Outputs for SubSystem: '<S1>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S1>/Switch Case' */

  /* SwitchCase: '<S2>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status1'
   */
  switch ((int32_T)rtU.yaw_status1) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S2>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S153>/Action Port'
     */
    /* Sum: '<S153>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm1'
     *  Inport: '<Root>/yaw_target1'
     */
    rtb_Sum_pp = rtU.yaw_target1 - rtU.yaw_speed_rpm1;

    /* Gain: '<S190>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S182>/Filter'
     *  Gain: '<S181>/Derivative Gain'
     *  Sum: '<S182>/SumD'
     */
    rtb_FilterCoefficient_k = (rtP.Kd_s_1 * rtb_Sum_pp - rtDW.Filter_DSTATE_k) *
      100.0;

    /* Sum: '<S196>/Sum' incorporates:
     *  DiscreteIntegrator: '<S187>/Integrator'
     *  Gain: '<S192>/Proportional Gain'
     */
    u0 = (rtP.Kp_s_1 * rtb_Sum_pp + rtDW.Integrator_DSTATE_lm) +
      rtb_FilterCoefficient_k;

    /* Saturate: '<S194>/Saturation' */
    if (u0 > 16384.0) {
      /* Outport: '<Root>/yaw_SPD_OUT1' */
      rtY.yaw_SPD_OUT1 = 16384.0;
    } else if (u0 < -16384.0) {
      /* Outport: '<Root>/yaw_SPD_OUT1' */
      rtY.yaw_SPD_OUT1 = -16384.0;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT1' */
      rtY.yaw_SPD_OUT1 = u0;
    }

    /* End of Saturate: '<S194>/Saturation' */

    /* Update for DiscreteIntegrator: '<S182>/Filter' */
    rtDW.Filter_DSTATE_k += 0.001 * rtb_FilterCoefficient_k;

    /* Update for DiscreteIntegrator: '<S187>/Integrator' incorporates:
     *  Gain: '<S184>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_lm += rtP.Ki_s_1 * rtb_Sum_pp * 0.001;

    /* End of Outputs for SubSystem: '<S2>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S2>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S154>/Action Port'
     */
    /* Sum: '<S154>/Sum' incorporates:
     *  Gain: '<S154>/Gain'
     *  Inport: '<Root>/yaw_circle1'
     *  Inport: '<Root>/yaw_ecd1'
     *  Inport: '<Root>/yaw_target1'
     *  Sum: '<S154>/Sum2'
     */
    rtb_FilterCoefficient_k = rtU.yaw_target1 - (8191.0 * rtU.yaw_circle1 +
      rtU.yaw_ecd1);

    /* Abs: '<S154>/Abs' */
    rtb_Sum_pp = fabs(rtb_FilterCoefficient_k);

    /* Switch: '<S154>/Switch2' incorporates:
     *  Constant: '<S154>/Constant'
     */
    if (!(rtb_Sum_pp > rtP.DeadBand)) {
      rtb_FilterCoefficient_k = 0.0;
    }

    /* End of Switch: '<S154>/Switch2' */

    /* Gain: '<S289>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S281>/Filter'
     *  Gain: '<S280>/Derivative Gain'
     *  Sum: '<S281>/SumD'
     */
    rtb_FilterCoefficient_m = (rtP.Kd_a_1 * rtb_FilterCoefficient_k -
      rtDW.Filter_DSTATE) * 100.0;

    /* Switch: '<S154>/Switch1' incorporates:
     *  Constant: '<S154>/Constant'
     *  Gain: '<S154>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm1'
     *  Saturate: '<S293>/Saturation'
     *  Sum: '<S154>/Sum1'
     */
    if (rtb_Sum_pp > rtP.DeadBand) {
      /* Sum: '<S295>/Sum' incorporates:
       *  DiscreteIntegrator: '<S286>/Integrator'
       *  Gain: '<S291>/Proportional Gain'
       */
      u0 = (rtP.Kp_a_1 * rtb_FilterCoefficient_k + rtDW.Integrator_DSTATE) +
        rtb_FilterCoefficient_m;

      /* Saturate: '<S293>/Saturation' */
      if (u0 > 16384.0) {
        u0 = 16384.0;
      } else if (u0 < -16384.0) {
        u0 = -16384.0;
      }

      rtb_Sum_pp = rtP.trans * u0 - rtU.yaw_speed_rpm1;
    } else {
      rtb_Sum_pp = 0.0;
    }

    /* End of Switch: '<S154>/Switch1' */

    /* Gain: '<S241>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S233>/Filter'
     *  Gain: '<S232>/Derivative Gain'
     *  Sum: '<S233>/SumD'
     */
    rtb_FilterCoefficient_n = (rtP.Kd_s_1 * rtb_Sum_pp - rtDW.Filter_DSTATE_j) *
      100.0;

    /* Sum: '<S247>/Sum' incorporates:
     *  DiscreteIntegrator: '<S238>/Integrator'
     *  Gain: '<S243>/Proportional Gain'
     */
    u0 = (rtP.Kp_s_1 * rtb_Sum_pp + rtDW.Integrator_DSTATE_l) +
      rtb_FilterCoefficient_n;

    /* Saturate: '<S245>/Saturation' */
    if (u0 > 16384.0) {
      /* Outport: '<Root>/yaw_ANG_OUT1' */
      rtY.yaw_ANG_OUT1 = 16384.0;
    } else if (u0 < -16384.0) {
      /* Outport: '<Root>/yaw_ANG_OUT1' */
      rtY.yaw_ANG_OUT1 = -16384.0;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT1' */
      rtY.yaw_ANG_OUT1 = u0;
    }

    /* End of Saturate: '<S245>/Saturation' */

    /* Chart: '<S154>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd1'
     *  Inport: '<Root>/yaw_last_ecd1'
     *  Sum: '<S154>/Sum3'
     */
    Chart1(rtU.yaw_ecd1 - rtU.yaw_last_ecd1, &rtDW.u2, &rtDW.sf_Chart1_f);

    /* Outport: '<Root>/yaw_circle_out1' incorporates:
     *  Inport: '<Root>/yaw_circle1'
     *  Sum: '<S154>/Sum4'
     */
    rtY.yaw_circle_out1 = rtDW.u2 + rtU.yaw_circle1;

    /* Update for DiscreteIntegrator: '<S286>/Integrator' incorporates:
     *  Gain: '<S283>/Integral Gain'
     */
    rtDW.Integrator_DSTATE += rtP.Ki_a_1 * rtb_FilterCoefficient_k * 0.001;

    /* Update for DiscreteIntegrator: '<S281>/Filter' */
    rtDW.Filter_DSTATE += 0.001 * rtb_FilterCoefficient_m;

    /* Update for DiscreteIntegrator: '<S233>/Filter' */
    rtDW.Filter_DSTATE_j += 0.001 * rtb_FilterCoefficient_n;

    /* Update for DiscreteIntegrator: '<S238>/Integrator' incorporates:
     *  Gain: '<S235>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_l += rtP.Ki_s_1 * rtb_Sum_pp * 0.001;

    /* End of Outputs for SubSystem: '<S2>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S2>/Switch Case' */
}

/* Model initialize function */
void PID_MODEL_initialize(void)
{
  /* SystemInitialize for IfAction SubSystem: '<S1>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S4>/Chart1' */
  Chart1_Init(&rtDW.u2_o);

  /* End of SystemInitialize for SubSystem: '<S1>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S2>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S154>/Chart1' */
  Chart1_Init(&rtDW.u2);

  /* End of SystemInitialize for SubSystem: '<S2>/If Action_speed Subsystem1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

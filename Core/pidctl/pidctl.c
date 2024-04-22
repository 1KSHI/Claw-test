/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pidctl.c
 *
 * Code generated for Simulink model 'pidctl'.
 *
 * Model version                  : 2.24
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Apr 20 23:59:25 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "pidctl.h"
#include "rtwtypes.h"
#include <math.h>

/* Named constants for Chart: '<S18>/Chart1' */
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
static void Chart1_Init(real32_T *rty_u2);
static void Chart1(real32_T rtu_u1, real32_T *rty_u2, DW_Chart1 *localDW);

/*
 * System initialize for atomic system:
 *    '<S18>/Chart1'
 *    '<S168>/Chart1'
 *    '<S318>/Chart1'
 *    '<S468>/Chart1'
 *    '<S618>/Chart1'
 *    '<S768>/Chart1'
 *    '<S918>/Chart1'
 *    '<S1068>/Chart1'
 *    '<S1218>/Chart1'
 *    '<S1368>/Chart1'
 *    ...
 */
static void Chart1_Init(real32_T *rty_u2)
{
  *rty_u2 = 0.0F;
}

/*
 * Output and update for atomic system:
 *    '<S18>/Chart1'
 *    '<S168>/Chart1'
 *    '<S318>/Chart1'
 *    '<S468>/Chart1'
 *    '<S618>/Chart1'
 *    '<S768>/Chart1'
 *    '<S918>/Chart1'
 *    '<S1068>/Chart1'
 *    '<S1218>/Chart1'
 *    '<S1368>/Chart1'
 *    ...
 */
static void Chart1(real32_T rtu_u1, real32_T *rty_u2, DW_Chart1 *localDW)
{
  /* Chart: '<S18>/Chart1' */
  if (localDW->is_active_c1_pidctl == 0U) {
    localDW->is_active_c1_pidctl = 1U;
    localDW->is_c1_pidctl = IN_IDLE;
  } else {
    switch (localDW->is_c1_pidctl) {
     case IN_ADD:
      if (rtu_u1 <= -5000.0F) {
        localDW->is_c1_pidctl = IN_SUB;
        *rty_u2 = -1.0F;
      } else if ((rtu_u1 < 5000.0F) && (rtu_u1 > -5000.0F)) {
        localDW->is_c1_pidctl = IN_IDLE;
      }
      break;

     case IN_IDLE:
      if (rtu_u1 >= 5000.0F) {
        localDW->is_c1_pidctl = IN_ADD;
        *rty_u2 = 1.0F;
      } else if (rtu_u1 <= -5000.0F) {
        localDW->is_c1_pidctl = IN_SUB;
        *rty_u2 = -1.0F;
      } else {
        *rty_u2 = 0.0F;
      }
      break;

     default:
      /* case IN_SUB: */
      if (rtu_u1 >= 5000.0F) {
        localDW->is_c1_pidctl = IN_ADD;
        *rty_u2 = 1.0F;
      } else if ((rtu_u1 < 5000.0F) && (rtu_u1 > -5000.0F)) {
        localDW->is_c1_pidctl = IN_IDLE;
      }
      break;
    }
  }

  /* End of Chart: '<S18>/Chart1' */
}

/* Model step function */
void pidctl_step(void)
{
  real32_T rtb_FilterCoefficient_ce;
  real32_T rtb_FilterCoefficient_ga;
  real32_T rtb_FilterCoefficient_j4;
  real32_T rtb_Sum_is;
  real32_T u0;

  /* SwitchCase: '<S8>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status16'
   */
  switch ((int32_T)rtU.yaw_status16) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S8>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1067>/Action Port'
     */
    /* Sum: '<S1067>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm16'
     *  Inport: '<Root>/yaw_target16'
     */
    rtb_Sum_is = rtU.yaw_target16 - rtU.yaw_speed_rpm16;

    /* Gain: '<S1104>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1096>/Filter'
     *  Gain: '<S1095>/Derivative Gain'
     *  Sum: '<S1096>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH2_8 * rtb_Sum_is -
      rtDW.Filter_DSTATE_ko) * 100.0F;

    /* Sum: '<S1110>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1101>/Integrator'
     *  Gain: '<S1106>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_8 * rtb_Sum_is + rtDW.Integrator_DSTATE_m) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S1108>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT16' */
      rtY.yaw_SPD_OUT16 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT16' */
      rtY.yaw_SPD_OUT16 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT16' */
      rtY.yaw_SPD_OUT16 = u0;
    }

    /* End of Saturate: '<S1108>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1096>/Filter' */
    rtDW.Filter_DSTATE_ko += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S1101>/Integrator' incorporates:
     *  Gain: '<S1098>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_m += rtP.SPD_I_CH2_8 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S8>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S8>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1068>/Action Port'
     */
    /* Sum: '<S1068>/Sum' incorporates:
     *  Gain: '<S1068>/Gain'
     *  Inport: '<Root>/yaw_circle16'
     *  Inport: '<Root>/yaw_ecd16'
     *  Inport: '<Root>/yaw_target16'
     *  Sum: '<S1068>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target16 - (8191.0F * rtU.yaw_circle16 +
      rtU.yaw_ecd16);

    /* Abs: '<S1068>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S1068>/Switch2' incorporates:
     *  Constant: '<S1068>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH2_8)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S1068>/Switch2' */

    /* Gain: '<S1203>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1195>/Filter'
     *  Gain: '<S1194>/Derivative Gain'
     *  Sum: '<S1195>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH2_8 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_mr) * 100.0F;

    /* Switch: '<S1068>/Switch1' incorporates:
     *  Constant: '<S1068>/Constant'
     *  Gain: '<S1068>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm16'
     *  Saturate: '<S1207>/Saturation'
     *  Sum: '<S1068>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH2_8) {
      /* Sum: '<S1209>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1200>/Integrator'
       *  Gain: '<S1205>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH2_8 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_nv) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S1207>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH2_8 * u0 - rtU.yaw_speed_rpm16;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S1068>/Switch1' */

    /* Gain: '<S1155>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1147>/Filter'
     *  Gain: '<S1146>/Derivative Gain'
     *  Sum: '<S1147>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH2_8 * rtb_Sum_is -
      rtDW.Filter_DSTATE_fq) * 100.0F;

    /* Sum: '<S1161>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1152>/Integrator'
     *  Gain: '<S1157>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH2_8 * rtb_Sum_is + rtDW.Integrator_DSTATE_f) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S1159>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT16' */
      rtY.yaw_ANG_OUT16 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT16' */
      rtY.yaw_ANG_OUT16 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT16' */
      rtY.yaw_ANG_OUT16 = u0;
    }

    /* End of Saturate: '<S1159>/Saturation' */

    /* Chart: '<S1068>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd16'
     *  Inport: '<Root>/yaw_last_ecd16'
     *  Sum: '<S1068>/Sum3'
     */
    Chart1(rtU.yaw_ecd16 - rtU.yaw_last_ecd16, &rtDW.u2_i, &rtDW.sf_Chart1_d);

    /* Outport: '<Root>/yaw_circle_out16' incorporates:
     *  Inport: '<Root>/yaw_circle16'
     *  Sum: '<S1068>/Sum4'
     */
    rtY.yaw_circle_out16 = rtDW.u2_i + rtU.yaw_circle16;

    /* Update for DiscreteIntegrator: '<S1200>/Integrator' incorporates:
     *  Gain: '<S1197>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_nv += rtP.ANG_S_I_CH2_8 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1195>/Filter' */
    rtDW.Filter_DSTATE_mr += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S1147>/Filter' */
    rtDW.Filter_DSTATE_fq += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S1152>/Integrator' incorporates:
     *  Gain: '<S1149>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_f += rtP.ANG_A_I_CH2_8 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S8>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S8>/Switch Case' */

  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status1'
   */
  switch ((int32_T)rtU.yaw_status1) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S1>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    /* Sum: '<S17>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm1'
     *  Inport: '<Root>/yaw_target1'
     */
    rtb_Sum_is = rtU.yaw_target1 - rtU.yaw_speed_rpm1;

    /* Gain: '<S54>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S46>/Filter'
     *  Gain: '<S45>/Derivative Gain'
     *  Sum: '<S46>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH1_1 * rtb_Sum_is -
      rtDW.Filter_DSTATE_p4) * 100.0F;

    /* Sum: '<S60>/Sum' incorporates:
     *  DiscreteIntegrator: '<S51>/Integrator'
     *  Gain: '<S56>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_1 * rtb_Sum_is + rtDW.Integrator_DSTATE_ee) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S58>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT1' */
      rtY.yaw_SPD_OUT1 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT1' */
      rtY.yaw_SPD_OUT1 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT1' */
      rtY.yaw_SPD_OUT1 = u0;
    }

    /* End of Saturate: '<S58>/Saturation' */

    /* Update for DiscreteIntegrator: '<S46>/Filter' */
    rtDW.Filter_DSTATE_p4 += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S51>/Integrator' incorporates:
     *  Gain: '<S48>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ee += rtP.SPD_I_CH1_1 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S1>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S1>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    /* Sum: '<S18>/Sum' incorporates:
     *  Gain: '<S18>/Gain'
     *  Inport: '<Root>/yaw_circle1'
     *  Inport: '<Root>/yaw_ecd1'
     *  Inport: '<Root>/yaw_target1'
     *  Sum: '<S18>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target1 - (8191.0F * rtU.yaw_circle1 +
      rtU.yaw_ecd1);

    /* Abs: '<S18>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S18>/Switch2' incorporates:
     *  Constant: '<S18>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH1_1)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S18>/Switch2' */

    /* Gain: '<S153>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S145>/Filter'
     *  Gain: '<S144>/Derivative Gain'
     *  Sum: '<S145>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH1_1 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_gk) * 100.0F;

    /* Switch: '<S18>/Switch1' incorporates:
     *  Constant: '<S18>/Constant'
     *  Gain: '<S18>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm1'
     *  Saturate: '<S157>/Saturation'
     *  Sum: '<S18>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH1_1) {
      /* Sum: '<S159>/Sum' incorporates:
       *  DiscreteIntegrator: '<S150>/Integrator'
       *  Gain: '<S155>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH1_1 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_e1) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S157>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH1_1 * u0 - rtU.yaw_speed_rpm1;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S18>/Switch1' */

    /* Gain: '<S105>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S97>/Filter'
     *  Gain: '<S96>/Derivative Gain'
     *  Sum: '<S97>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH1_1 * rtb_Sum_is -
      rtDW.Filter_DSTATE_a3) * 100.0F;

    /* Sum: '<S111>/Sum' incorporates:
     *  DiscreteIntegrator: '<S102>/Integrator'
     *  Gain: '<S107>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH1_1 * rtb_Sum_is + rtDW.Integrator_DSTATE_fw) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S109>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT1' */
      rtY.yaw_ANG_OUT1 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT1' */
      rtY.yaw_ANG_OUT1 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT1' */
      rtY.yaw_ANG_OUT1 = u0;
    }

    /* End of Saturate: '<S109>/Saturation' */

    /* Chart: '<S18>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd1'
     *  Inport: '<Root>/yaw_last_ecd1'
     *  Sum: '<S18>/Sum3'
     */
    Chart1(rtU.yaw_ecd1 - rtU.yaw_last_ecd1, &rtDW.u2_e, &rtDW.sf_Chart1);

    /* Outport: '<Root>/yaw_circle_out1' incorporates:
     *  Inport: '<Root>/yaw_circle1'
     *  Sum: '<S18>/Sum4'
     */
    rtY.yaw_circle_out1 = rtDW.u2_e + rtU.yaw_circle1;

    /* Update for DiscreteIntegrator: '<S150>/Integrator' incorporates:
     *  Gain: '<S147>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_e1 += rtP.ANG_S_I_CH1_1 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S145>/Filter' */
    rtDW.Filter_DSTATE_gk += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S97>/Filter' */
    rtDW.Filter_DSTATE_a3 += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S102>/Integrator' incorporates:
     *  Gain: '<S99>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_fw += rtP.ANG_A_I_CH1_1 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S1>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S1>/Switch Case' */

  /* SwitchCase: '<S9>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status2'
   */
  switch ((int32_T)rtU.yaw_status2) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S9>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1217>/Action Port'
     */
    /* Sum: '<S1217>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm2'
     *  Inport: '<Root>/yaw_target2'
     */
    rtb_Sum_is = rtU.yaw_target2 - rtU.yaw_speed_rpm2;

    /* Gain: '<S1254>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1246>/Filter'
     *  Gain: '<S1245>/Derivative Gain'
     *  Sum: '<S1246>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH1_2 * rtb_Sum_is -
      rtDW.Filter_DSTATE_g4) * 100.0F;

    /* Sum: '<S1260>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1251>/Integrator'
     *  Gain: '<S1256>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_2 * rtb_Sum_is + rtDW.Integrator_DSTATE_g) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S1258>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT2' */
      rtY.yaw_SPD_OUT2 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT2' */
      rtY.yaw_SPD_OUT2 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT2' */
      rtY.yaw_SPD_OUT2 = u0;
    }

    /* End of Saturate: '<S1258>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1246>/Filter' */
    rtDW.Filter_DSTATE_g4 += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S1251>/Integrator' incorporates:
     *  Gain: '<S1248>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_g += rtP.SPD_I_CH1_2 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S9>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S9>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1218>/Action Port'
     */
    /* Sum: '<S1218>/Sum' incorporates:
     *  Gain: '<S1218>/Gain'
     *  Inport: '<Root>/yaw_circle2'
     *  Inport: '<Root>/yaw_ecd2'
     *  Inport: '<Root>/yaw_target2'
     *  Sum: '<S1218>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target2 - (8191.0F * rtU.yaw_circle2 +
      rtU.yaw_ecd2);

    /* Abs: '<S1218>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S1218>/Switch2' incorporates:
     *  Constant: '<S1218>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH1_2)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S1218>/Switch2' */

    /* Gain: '<S1353>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1345>/Filter'
     *  Gain: '<S1344>/Derivative Gain'
     *  Sum: '<S1345>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH1_2 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_c3) * 100.0F;

    /* Switch: '<S1218>/Switch1' incorporates:
     *  Constant: '<S1218>/Constant'
     *  Gain: '<S1218>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm2'
     *  Saturate: '<S1357>/Saturation'
     *  Sum: '<S1218>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH1_2) {
      /* Sum: '<S1359>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1350>/Integrator'
       *  Gain: '<S1355>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH1_2 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_pn) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S1357>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH1_2 * u0 - rtU.yaw_speed_rpm2;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S1218>/Switch1' */

    /* Gain: '<S1305>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1297>/Filter'
     *  Gain: '<S1296>/Derivative Gain'
     *  Sum: '<S1297>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH1_2 * rtb_Sum_is -
      rtDW.Filter_DSTATE_i0) * 100.0F;

    /* Sum: '<S1311>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1302>/Integrator'
     *  Gain: '<S1307>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH1_2 * rtb_Sum_is + rtDW.Integrator_DSTATE_ks) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S1309>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT2' */
      rtY.yaw_ANG_OUT2 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT2' */
      rtY.yaw_ANG_OUT2 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT2' */
      rtY.yaw_ANG_OUT2 = u0;
    }

    /* End of Saturate: '<S1309>/Saturation' */

    /* Chart: '<S1218>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd2'
     *  Inport: '<Root>/yaw_last_ecd2'
     *  Sum: '<S1218>/Sum3'
     */
    Chart1(rtU.yaw_ecd2 - rtU.yaw_last_ecd2, &rtDW.u2_gr, &rtDW.sf_Chart1_fk);

    /* Outport: '<Root>/yaw_circle_out2' incorporates:
     *  Inport: '<Root>/yaw_circle2'
     *  Sum: '<S1218>/Sum4'
     */
    rtY.yaw_circle_out2 = rtDW.u2_gr + rtU.yaw_circle2;

    /* Update for DiscreteIntegrator: '<S1350>/Integrator' incorporates:
     *  Gain: '<S1347>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_pn += rtP.ANG_S_I_CH1_2 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1345>/Filter' */
    rtDW.Filter_DSTATE_c3 += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S1297>/Filter' */
    rtDW.Filter_DSTATE_i0 += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S1302>/Integrator' incorporates:
     *  Gain: '<S1299>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ks += rtP.ANG_A_I_CH1_2 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S9>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S9>/Switch Case' */

  /* SwitchCase: '<S10>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status3'
   */
  switch ((int32_T)rtU.yaw_status3) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S10>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1367>/Action Port'
     */
    /* Sum: '<S1367>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm3'
     *  Inport: '<Root>/yaw_target3'
     */
    rtb_Sum_is = rtU.yaw_target3 - rtU.yaw_speed_rpm3;

    /* Gain: '<S1404>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1396>/Filter'
     *  Gain: '<S1395>/Derivative Gain'
     *  Sum: '<S1396>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH1_3 * rtb_Sum_is -
      rtDW.Filter_DSTATE_pm) * 100.0F;

    /* Sum: '<S1410>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1401>/Integrator'
     *  Gain: '<S1406>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_3 * rtb_Sum_is + rtDW.Integrator_DSTATE_ip) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S1408>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT3' */
      rtY.yaw_SPD_OUT3 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT3' */
      rtY.yaw_SPD_OUT3 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT3' */
      rtY.yaw_SPD_OUT3 = u0;
    }

    /* End of Saturate: '<S1408>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1396>/Filter' */
    rtDW.Filter_DSTATE_pm += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S1401>/Integrator' incorporates:
     *  Gain: '<S1398>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ip += rtP.SPD_I_CH1_3 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S10>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S10>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1368>/Action Port'
     */
    /* Sum: '<S1368>/Sum' incorporates:
     *  Gain: '<S1368>/Gain'
     *  Inport: '<Root>/yaw_circle3'
     *  Inport: '<Root>/yaw_ecd3'
     *  Inport: '<Root>/yaw_target3'
     *  Sum: '<S1368>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target3 - (8191.0F * rtU.yaw_circle3 +
      rtU.yaw_ecd3);

    /* Abs: '<S1368>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S1368>/Switch2' incorporates:
     *  Constant: '<S1368>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH1_3)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S1368>/Switch2' */

    /* Gain: '<S1503>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1495>/Filter'
     *  Gain: '<S1494>/Derivative Gain'
     *  Sum: '<S1495>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH1_3 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_c) * 100.0F;

    /* Switch: '<S1368>/Switch1' incorporates:
     *  Constant: '<S1368>/Constant'
     *  Gain: '<S1368>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm3'
     *  Saturate: '<S1507>/Saturation'
     *  Sum: '<S1368>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH1_3) {
      /* Sum: '<S1509>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1500>/Integrator'
       *  Gain: '<S1505>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH1_3 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_n) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S1507>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH1_3 * u0 - rtU.yaw_speed_rpm3;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S1368>/Switch1' */

    /* Gain: '<S1455>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1447>/Filter'
     *  Gain: '<S1446>/Derivative Gain'
     *  Sum: '<S1447>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH1_3 * rtb_Sum_is -
      rtDW.Filter_DSTATE_nb) * 100.0F;

    /* Sum: '<S1461>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1452>/Integrator'
     *  Gain: '<S1457>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH1_3 * rtb_Sum_is + rtDW.Integrator_DSTATE_nk) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S1459>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT3' */
      rtY.yaw_ANG_OUT3 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT3' */
      rtY.yaw_ANG_OUT3 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT3' */
      rtY.yaw_ANG_OUT3 = u0;
    }

    /* End of Saturate: '<S1459>/Saturation' */

    /* Chart: '<S1368>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd3'
     *  Inport: '<Root>/yaw_last_ecd3'
     *  Sum: '<S1368>/Sum3'
     */
    Chart1(rtU.yaw_ecd3 - rtU.yaw_last_ecd3, &rtDW.u2_g, &rtDW.sf_Chart1_gh);

    /* Outport: '<Root>/yaw_circle_out3' incorporates:
     *  Inport: '<Root>/yaw_circle3'
     *  Sum: '<S1368>/Sum4'
     */
    rtY.yaw_circle_out3 = rtDW.u2_g + rtU.yaw_circle3;

    /* Update for DiscreteIntegrator: '<S1500>/Integrator' incorporates:
     *  Gain: '<S1497>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_n += rtP.ANG_S_I_CH1_3 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1495>/Filter' */
    rtDW.Filter_DSTATE_c += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S1447>/Filter' */
    rtDW.Filter_DSTATE_nb += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S1452>/Integrator' incorporates:
     *  Gain: '<S1449>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_nk += rtP.ANG_A_I_CH1_3 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S10>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S10>/Switch Case' */

  /* SwitchCase: '<S11>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status4'
   */
  switch ((int32_T)rtU.yaw_status4) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S11>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1517>/Action Port'
     */
    /* Sum: '<S1517>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm4'
     *  Inport: '<Root>/yaw_target4'
     */
    rtb_Sum_is = rtU.yaw_target4 - rtU.yaw_speed_rpm4;

    /* Gain: '<S1554>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1546>/Filter'
     *  Gain: '<S1545>/Derivative Gain'
     *  Sum: '<S1546>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH1_4 * rtb_Sum_is -
      rtDW.Filter_DSTATE_i1) * 100.0F;

    /* Sum: '<S1560>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1551>/Integrator'
     *  Gain: '<S1556>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_4 * rtb_Sum_is + rtDW.Integrator_DSTATE_bn) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S1558>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT4' */
      rtY.yaw_SPD_OUT4 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT4' */
      rtY.yaw_SPD_OUT4 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT4' */
      rtY.yaw_SPD_OUT4 = u0;
    }

    /* End of Saturate: '<S1558>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1546>/Filter' */
    rtDW.Filter_DSTATE_i1 += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S1551>/Integrator' incorporates:
     *  Gain: '<S1548>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_bn += rtP.SPD_I_CH1_4 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S11>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S11>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1518>/Action Port'
     */
    /* Sum: '<S1518>/Sum' incorporates:
     *  Gain: '<S1518>/Gain'
     *  Inport: '<Root>/yaw_circle4'
     *  Inport: '<Root>/yaw_ecd4'
     *  Inport: '<Root>/yaw_target4'
     *  Sum: '<S1518>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target4 - (8191.0F * rtU.yaw_circle4 +
      rtU.yaw_ecd4);

    /* Abs: '<S1518>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S1518>/Switch2' incorporates:
     *  Constant: '<S1518>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH1_4)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S1518>/Switch2' */

    /* Gain: '<S1653>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1645>/Filter'
     *  Gain: '<S1644>/Derivative Gain'
     *  Sum: '<S1645>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH1_4 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_n) * 100.0F;

    /* Switch: '<S1518>/Switch1' incorporates:
     *  Constant: '<S1518>/Constant'
     *  Gain: '<S1518>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm4'
     *  Saturate: '<S1657>/Saturation'
     *  Sum: '<S1518>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH1_4) {
      /* Sum: '<S1659>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1650>/Integrator'
       *  Gain: '<S1655>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH1_4 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_p) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S1657>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH1_4 * u0 - rtU.yaw_speed_rpm4;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S1518>/Switch1' */

    /* Gain: '<S1605>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1597>/Filter'
     *  Gain: '<S1596>/Derivative Gain'
     *  Sum: '<S1597>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH1_4 * rtb_Sum_is -
      rtDW.Filter_DSTATE_j) * 100.0F;

    /* Sum: '<S1611>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1602>/Integrator'
     *  Gain: '<S1607>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH1_4 * rtb_Sum_is + rtDW.Integrator_DSTATE_di) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S1609>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT4' */
      rtY.yaw_ANG_OUT4 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT4' */
      rtY.yaw_ANG_OUT4 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT4' */
      rtY.yaw_ANG_OUT4 = u0;
    }

    /* End of Saturate: '<S1609>/Saturation' */

    /* Chart: '<S1518>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd4'
     *  Inport: '<Root>/yaw_last_ecd4'
     *  Sum: '<S1518>/Sum3'
     */
    Chart1(rtU.yaw_ecd4 - rtU.yaw_last_ecd4, &rtDW.u2_f, &rtDW.sf_Chart1_f1);

    /* Outport: '<Root>/yaw_circle_out4' incorporates:
     *  Inport: '<Root>/yaw_circle4'
     *  Sum: '<S1518>/Sum4'
     */
    rtY.yaw_circle_out4 = rtDW.u2_f + rtU.yaw_circle4;

    /* Update for DiscreteIntegrator: '<S1650>/Integrator' incorporates:
     *  Gain: '<S1647>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_p += rtP.ANG_S_I_CH1_4 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1645>/Filter' */
    rtDW.Filter_DSTATE_n += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S1597>/Filter' */
    rtDW.Filter_DSTATE_j += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S1602>/Integrator' incorporates:
     *  Gain: '<S1599>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_di += rtP.ANG_A_I_CH1_4 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S11>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S11>/Switch Case' */

  /* SwitchCase: '<S12>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status5'
   */
  switch ((int32_T)rtU.yaw_status5) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S12>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1667>/Action Port'
     */
    /* Sum: '<S1667>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm5'
     *  Inport: '<Root>/yaw_target5'
     */
    rtb_Sum_is = rtU.yaw_target5 - rtU.yaw_speed_rpm5;

    /* Gain: '<S1704>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1696>/Filter'
     *  Gain: '<S1695>/Derivative Gain'
     *  Sum: '<S1696>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH1_5 * rtb_Sum_is -
      rtDW.Filter_DSTATE_l) * 100.0F;

    /* Sum: '<S1710>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1701>/Integrator'
     *  Gain: '<S1706>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_5 * rtb_Sum_is + rtDW.Integrator_DSTATE_a) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S1708>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT5' */
      rtY.yaw_SPD_OUT5 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT5' */
      rtY.yaw_SPD_OUT5 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT5' */
      rtY.yaw_SPD_OUT5 = u0;
    }

    /* End of Saturate: '<S1708>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1696>/Filter' */
    rtDW.Filter_DSTATE_l += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S1701>/Integrator' incorporates:
     *  Gain: '<S1698>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_a += rtP.SPD_I_CH1_5 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S12>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S12>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1668>/Action Port'
     */
    /* Sum: '<S1668>/Sum' incorporates:
     *  Gain: '<S1668>/Gain'
     *  Inport: '<Root>/yaw_circle5'
     *  Inport: '<Root>/yaw_ecd5'
     *  Inport: '<Root>/yaw_target5'
     *  Sum: '<S1668>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target5 - (8191.0F * rtU.yaw_circle5 +
      rtU.yaw_ecd5);

    /* Abs: '<S1668>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S1668>/Switch2' incorporates:
     *  Constant: '<S1668>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH1_5)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S1668>/Switch2' */

    /* Gain: '<S1803>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1795>/Filter'
     *  Gain: '<S1794>/Derivative Gain'
     *  Sum: '<S1795>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH1_5 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_k) * 100.0F;

    /* Switch: '<S1668>/Switch1' incorporates:
     *  Constant: '<S1668>/Constant'
     *  Gain: '<S1668>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm5'
     *  Saturate: '<S1807>/Saturation'
     *  Sum: '<S1668>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH1_5) {
      /* Sum: '<S1809>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1800>/Integrator'
       *  Gain: '<S1805>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH1_5 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_je) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S1807>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH1_5 * u0 - rtU.yaw_speed_rpm5;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S1668>/Switch1' */

    /* Gain: '<S1755>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1747>/Filter'
     *  Gain: '<S1746>/Derivative Gain'
     *  Sum: '<S1747>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH1_5 * rtb_Sum_is -
      rtDW.Filter_DSTATE_is) * 100.0F;

    /* Sum: '<S1761>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1752>/Integrator'
     *  Gain: '<S1757>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH1_5 * rtb_Sum_is + rtDW.Integrator_DSTATE_e) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S1759>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT5' */
      rtY.yaw_ANG_OUT5 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT5' */
      rtY.yaw_ANG_OUT5 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT5' */
      rtY.yaw_ANG_OUT5 = u0;
    }

    /* End of Saturate: '<S1759>/Saturation' */

    /* Chart: '<S1668>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd5'
     *  Inport: '<Root>/yaw_last_ecd5'
     *  Sum: '<S1668>/Sum3'
     */
    Chart1(rtU.yaw_ecd5 - rtU.yaw_last_ecd5, &rtDW.u2_b, &rtDW.sf_Chart1_oc);

    /* Outport: '<Root>/yaw_circle_out5' incorporates:
     *  Inport: '<Root>/yaw_circle5'
     *  Sum: '<S1668>/Sum4'
     */
    rtY.yaw_circle_out5 = rtDW.u2_b + rtU.yaw_circle5;

    /* Update for DiscreteIntegrator: '<S1800>/Integrator' incorporates:
     *  Gain: '<S1797>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_je += rtP.ANG_S_I_CH1_5 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1795>/Filter' */
    rtDW.Filter_DSTATE_k += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S1747>/Filter' */
    rtDW.Filter_DSTATE_is += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S1752>/Integrator' incorporates:
     *  Gain: '<S1749>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_e += rtP.ANG_A_I_CH1_5 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S12>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S12>/Switch Case' */

  /* SwitchCase: '<S13>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status6'
   */
  switch ((int32_T)rtU.yaw_status6) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S13>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1817>/Action Port'
     */
    /* Sum: '<S1817>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm6'
     *  Inport: '<Root>/yaw_target6'
     */
    rtb_Sum_is = rtU.yaw_target6 - rtU.yaw_speed_rpm6;

    /* Gain: '<S1854>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1846>/Filter'
     *  Gain: '<S1845>/Derivative Gain'
     *  Sum: '<S1846>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH1_6 * rtb_Sum_is -
      rtDW.Filter_DSTATE_fb) * 100.0F;

    /* Sum: '<S1860>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1851>/Integrator'
     *  Gain: '<S1856>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_6 * rtb_Sum_is + rtDW.Integrator_DSTATE_jd) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S1858>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT6' */
      rtY.yaw_SPD_OUT6 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT6' */
      rtY.yaw_SPD_OUT6 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT6' */
      rtY.yaw_SPD_OUT6 = u0;
    }

    /* End of Saturate: '<S1858>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1846>/Filter' */
    rtDW.Filter_DSTATE_fb += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S1851>/Integrator' incorporates:
     *  Gain: '<S1848>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_jd += rtP.SPD_I_CH1_6 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S13>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S13>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1818>/Action Port'
     */
    /* Sum: '<S1818>/Sum' incorporates:
     *  Gain: '<S1818>/Gain'
     *  Inport: '<Root>/yaw_circle6'
     *  Inport: '<Root>/yaw_ecd6'
     *  Inport: '<Root>/yaw_target6'
     *  Sum: '<S1818>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target6 - (8191.0F * rtU.yaw_circle6 +
      rtU.yaw_ecd6);

    /* Abs: '<S1818>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S1818>/Switch2' incorporates:
     *  Constant: '<S1818>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH1_6)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S1818>/Switch2' */

    /* Gain: '<S1953>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1945>/Filter'
     *  Gain: '<S1944>/Derivative Gain'
     *  Sum: '<S1945>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH1_6 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_a) * 100.0F;

    /* Switch: '<S1818>/Switch1' incorporates:
     *  Constant: '<S1818>/Constant'
     *  Gain: '<S1818>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm6'
     *  Saturate: '<S1957>/Saturation'
     *  Sum: '<S1818>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH1_6) {
      /* Sum: '<S1959>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1950>/Integrator'
       *  Gain: '<S1955>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH1_6 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_d) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S1957>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH1_6 * u0 - rtU.yaw_speed_rpm6;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S1818>/Switch1' */

    /* Gain: '<S1905>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1897>/Filter'
     *  Gain: '<S1896>/Derivative Gain'
     *  Sum: '<S1897>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH1_6 * rtb_Sum_is -
      rtDW.Filter_DSTATE_h) * 100.0F;

    /* Sum: '<S1911>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1902>/Integrator'
     *  Gain: '<S1907>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH1_6 * rtb_Sum_is + rtDW.Integrator_DSTATE_kq) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S1909>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT6' */
      rtY.yaw_ANG_OUT6 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT6' */
      rtY.yaw_ANG_OUT6 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT6' */
      rtY.yaw_ANG_OUT6 = u0;
    }

    /* End of Saturate: '<S1909>/Saturation' */

    /* Chart: '<S1818>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd6'
     *  Inport: '<Root>/yaw_last_ecd6'
     *  Sum: '<S1818>/Sum3'
     */
    Chart1(rtU.yaw_ecd6 - rtU.yaw_last_ecd6, &rtDW.u2_l, &rtDW.sf_Chart1_g2);

    /* Outport: '<Root>/yaw_circle_out6' incorporates:
     *  Inport: '<Root>/yaw_circle6'
     *  Sum: '<S1818>/Sum4'
     */
    rtY.yaw_circle_out6 = rtDW.u2_l + rtU.yaw_circle6;

    /* Update for DiscreteIntegrator: '<S1950>/Integrator' incorporates:
     *  Gain: '<S1947>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_d += rtP.ANG_S_I_CH1_6 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1945>/Filter' */
    rtDW.Filter_DSTATE_a += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S1897>/Filter' */
    rtDW.Filter_DSTATE_h += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S1902>/Integrator' incorporates:
     *  Gain: '<S1899>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_kq += rtP.ANG_A_I_CH1_6 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S13>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S13>/Switch Case' */

  /* SwitchCase: '<S14>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status7'
   */
  switch ((int32_T)rtU.yaw_status7) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S14>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1967>/Action Port'
     */
    /* Sum: '<S1967>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm7'
     *  Inport: '<Root>/yaw_target7'
     */
    rtb_Sum_is = rtU.yaw_target7 - rtU.yaw_speed_rpm7;

    /* Gain: '<S2004>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1996>/Filter'
     *  Gain: '<S1995>/Derivative Gain'
     *  Sum: '<S1996>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH1_7 * rtb_Sum_is -
      rtDW.Filter_DSTATE_i) * 100.0F;

    /* Sum: '<S2010>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2001>/Integrator'
     *  Gain: '<S2006>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_7 * rtb_Sum_is + rtDW.Integrator_DSTATE_ho) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S2008>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT7' */
      rtY.yaw_SPD_OUT7 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT7' */
      rtY.yaw_SPD_OUT7 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT7' */
      rtY.yaw_SPD_OUT7 = u0;
    }

    /* End of Saturate: '<S2008>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1996>/Filter' */
    rtDW.Filter_DSTATE_i += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S2001>/Integrator' incorporates:
     *  Gain: '<S1998>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ho += rtP.SPD_I_CH1_7 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S14>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S14>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1968>/Action Port'
     */
    /* Sum: '<S1968>/Sum' incorporates:
     *  Gain: '<S1968>/Gain'
     *  Inport: '<Root>/yaw_circle7'
     *  Inport: '<Root>/yaw_ecd7'
     *  Inport: '<Root>/yaw_target7'
     *  Sum: '<S1968>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target7 - (8191.0F * rtU.yaw_circle7 +
      rtU.yaw_ecd7);

    /* Abs: '<S1968>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S1968>/Switch2' incorporates:
     *  Constant: '<S1968>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH1_7)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S1968>/Switch2' */

    /* Gain: '<S2103>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2095>/Filter'
     *  Gain: '<S2094>/Derivative Gain'
     *  Sum: '<S2095>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH1_7 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_g) * 100.0F;

    /* Switch: '<S1968>/Switch1' incorporates:
     *  Constant: '<S1968>/Constant'
     *  Gain: '<S1968>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm7'
     *  Saturate: '<S2107>/Saturation'
     *  Sum: '<S1968>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH1_7) {
      /* Sum: '<S2109>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2100>/Integrator'
       *  Gain: '<S2105>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH1_7 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_i) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S2107>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH1_7 * u0 - rtU.yaw_speed_rpm7;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S1968>/Switch1' */

    /* Gain: '<S2055>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2047>/Filter'
     *  Gain: '<S2046>/Derivative Gain'
     *  Sum: '<S2047>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH1_7 * rtb_Sum_is -
      rtDW.Filter_DSTATE_f5) * 100.0F;

    /* Sum: '<S2061>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2052>/Integrator'
     *  Gain: '<S2057>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH1_7 * rtb_Sum_is + rtDW.Integrator_DSTATE_l) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S2059>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT7' */
      rtY.yaw_ANG_OUT7 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT7' */
      rtY.yaw_ANG_OUT7 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT7' */
      rtY.yaw_ANG_OUT7 = u0;
    }

    /* End of Saturate: '<S2059>/Saturation' */

    /* Chart: '<S1968>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd7'
     *  Inport: '<Root>/yaw_last_ecd7'
     *  Sum: '<S1968>/Sum3'
     */
    Chart1(rtU.yaw_ecd7 - rtU.yaw_last_ecd7, &rtDW.u2_n, &rtDW.sf_Chart1_h);

    /* Outport: '<Root>/yaw_circle_out7' incorporates:
     *  Inport: '<Root>/yaw_circle7'
     *  Sum: '<S1968>/Sum4'
     */
    rtY.yaw_circle_out7 = rtDW.u2_n + rtU.yaw_circle7;

    /* Update for DiscreteIntegrator: '<S2100>/Integrator' incorporates:
     *  Gain: '<S2097>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_i += rtP.ANG_S_I_CH1_7 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2095>/Filter' */
    rtDW.Filter_DSTATE_g += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S2047>/Filter' */
    rtDW.Filter_DSTATE_f5 += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S2052>/Integrator' incorporates:
     *  Gain: '<S2049>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_l += rtP.ANG_A_I_CH1_7 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S14>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S14>/Switch Case' */

  /* SwitchCase: '<S15>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status8'
   */
  switch ((int32_T)rtU.yaw_status8) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S15>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S2117>/Action Port'
     */
    /* Sum: '<S2117>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm8'
     *  Inport: '<Root>/yaw_target8'
     */
    rtb_Sum_is = rtU.yaw_target8 - rtU.yaw_speed_rpm8;

    /* Gain: '<S2154>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2146>/Filter'
     *  Gain: '<S2145>/Derivative Gain'
     *  Sum: '<S2146>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH1_8 * rtb_Sum_is -
      rtDW.Filter_DSTATE_m) * 100.0F;

    /* Sum: '<S2160>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2151>/Integrator'
     *  Gain: '<S2156>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_8 * rtb_Sum_is + rtDW.Integrator_DSTATE_h) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S2158>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT8' */
      rtY.yaw_SPD_OUT8 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT8' */
      rtY.yaw_SPD_OUT8 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT8' */
      rtY.yaw_SPD_OUT8 = u0;
    }

    /* End of Saturate: '<S2158>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2146>/Filter' */
    rtDW.Filter_DSTATE_m += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S2151>/Integrator' incorporates:
     *  Gain: '<S2148>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_h += rtP.SPD_I_CH1_8 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S15>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S15>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2118>/Action Port'
     */
    /* Sum: '<S2118>/Sum' incorporates:
     *  Gain: '<S2118>/Gain'
     *  Inport: '<Root>/yaw_circle8'
     *  Inport: '<Root>/yaw_ecd8'
     *  Inport: '<Root>/yaw_target8'
     *  Sum: '<S2118>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target8 - (8191.0F * rtU.yaw_circle8 +
      rtU.yaw_ecd8);

    /* Abs: '<S2118>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S2118>/Switch2' incorporates:
     *  Constant: '<S2118>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH1_8)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S2118>/Switch2' */

    /* Gain: '<S2253>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2245>/Filter'
     *  Gain: '<S2244>/Derivative Gain'
     *  Sum: '<S2245>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH1_8 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_f) * 100.0F;

    /* Switch: '<S2118>/Switch1' incorporates:
     *  Constant: '<S2118>/Constant'
     *  Gain: '<S2118>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm8'
     *  Saturate: '<S2257>/Saturation'
     *  Sum: '<S2118>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH1_8) {
      /* Sum: '<S2259>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2250>/Integrator'
       *  Gain: '<S2255>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH1_8 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_j) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S2257>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH1_8 * u0 - rtU.yaw_speed_rpm8;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S2118>/Switch1' */

    /* Gain: '<S2205>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2197>/Filter'
     *  Gain: '<S2196>/Derivative Gain'
     *  Sum: '<S2197>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH1_8 * rtb_Sum_is -
      rtDW.Filter_DSTATE_pb) * 100.0F;

    /* Sum: '<S2211>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2202>/Integrator'
     *  Gain: '<S2207>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH1_8 * rtb_Sum_is + rtDW.Integrator_DSTATE_o) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S2209>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT8' */
      rtY.yaw_ANG_OUT8 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT8' */
      rtY.yaw_ANG_OUT8 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT8' */
      rtY.yaw_ANG_OUT8 = u0;
    }

    /* End of Saturate: '<S2209>/Saturation' */

    /* Chart: '<S2118>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd8'
     *  Inport: '<Root>/yaw_last_ecd8'
     *  Sum: '<S2118>/Sum3'
     */
    Chart1(rtU.yaw_ecd8 - rtU.yaw_last_ecd8, &rtDW.u2_d, &rtDW.sf_Chart1_op);

    /* Outport: '<Root>/yaw_circle_out8' incorporates:
     *  Inport: '<Root>/yaw_circle8'
     *  Sum: '<S2118>/Sum4'
     */
    rtY.yaw_circle_out8 = rtDW.u2_d + rtU.yaw_circle8;

    /* Update for DiscreteIntegrator: '<S2250>/Integrator' incorporates:
     *  Gain: '<S2247>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_j += rtP.ANG_S_I_CH1_8 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2245>/Filter' */
    rtDW.Filter_DSTATE_f += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S2197>/Filter' */
    rtDW.Filter_DSTATE_pb += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S2202>/Integrator' incorporates:
     *  Gain: '<S2199>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_o += rtP.ANG_A_I_CH1_8 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S15>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S15>/Switch Case' */

  /* SwitchCase: '<S16>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status9'
   */
  switch ((int32_T)rtU.yaw_status9) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S16>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S2267>/Action Port'
     */
    /* Sum: '<S2267>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm9'
     *  Inport: '<Root>/yaw_target9'
     */
    rtb_Sum_is = rtU.yaw_target9 - rtU.yaw_speed_rpm9;

    /* Gain: '<S2304>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2296>/Filter'
     *  Gain: '<S2295>/Derivative Gain'
     *  Sum: '<S2296>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH2_1 * rtb_Sum_is -
      rtDW.Filter_DSTATE_p) * 100.0F;

    /* Sum: '<S2310>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2301>/Integrator'
     *  Gain: '<S2306>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_1 * rtb_Sum_is + rtDW.Integrator_DSTATE_k) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S2308>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT9' */
      rtY.yaw_SPD_OUT9 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT9' */
      rtY.yaw_SPD_OUT9 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT9' */
      rtY.yaw_SPD_OUT9 = u0;
    }

    /* End of Saturate: '<S2308>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2296>/Filter' */
    rtDW.Filter_DSTATE_p += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S2301>/Integrator' incorporates:
     *  Gain: '<S2298>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_k += rtP.SPD_I_CH2_1 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S16>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S16>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2268>/Action Port'
     */
    /* Sum: '<S2268>/Sum' incorporates:
     *  Gain: '<S2268>/Gain'
     *  Inport: '<Root>/yaw_circle9'
     *  Inport: '<Root>/yaw_ecd9'
     *  Inport: '<Root>/yaw_target9'
     *  Sum: '<S2268>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target9 - (8191.0F * rtU.yaw_circle9 +
      rtU.yaw_ecd9);

    /* Abs: '<S2268>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S2268>/Switch2' incorporates:
     *  Constant: '<S2268>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH2_1)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S2268>/Switch2' */

    /* Gain: '<S2403>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2395>/Filter'
     *  Gain: '<S2394>/Derivative Gain'
     *  Sum: '<S2395>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH2_1 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE) * 100.0F;

    /* Switch: '<S2268>/Switch1' incorporates:
     *  Constant: '<S2268>/Constant'
     *  Gain: '<S2268>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm9'
     *  Saturate: '<S2407>/Saturation'
     *  Sum: '<S2268>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH2_1) {
      /* Sum: '<S2409>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2400>/Integrator'
       *  Gain: '<S2405>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH2_1 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S2407>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH2_1 * u0 - rtU.yaw_speed_rpm9;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S2268>/Switch1' */

    /* Gain: '<S2355>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2347>/Filter'
     *  Gain: '<S2346>/Derivative Gain'
     *  Sum: '<S2347>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH2_1 * rtb_Sum_is -
      rtDW.Filter_DSTATE_d) * 100.0F;

    /* Sum: '<S2361>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2352>/Integrator'
     *  Gain: '<S2357>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH2_1 * rtb_Sum_is + rtDW.Integrator_DSTATE_b) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S2359>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT9' */
      rtY.yaw_ANG_OUT9 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT9' */
      rtY.yaw_ANG_OUT9 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT9' */
      rtY.yaw_ANG_OUT9 = u0;
    }

    /* End of Saturate: '<S2359>/Saturation' */

    /* Chart: '<S2268>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd9'
     *  Inport: '<Root>/yaw_last_ecd9'
     *  Sum: '<S2268>/Sum3'
     */
    Chart1(rtU.yaw_ecd9 - rtU.yaw_last_ecd9, &rtDW.u2, &rtDW.sf_Chart1_bf);

    /* Outport: '<Root>/yaw_circle_out9' incorporates:
     *  Inport: '<Root>/yaw_circle9'
     *  Sum: '<S2268>/Sum4'
     */
    rtY.yaw_circle_out9 = rtDW.u2 + rtU.yaw_circle9;

    /* Update for DiscreteIntegrator: '<S2400>/Integrator' incorporates:
     *  Gain: '<S2397>/Integral Gain'
     */
    rtDW.Integrator_DSTATE += rtP.ANG_S_I_CH2_1 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2395>/Filter' */
    rtDW.Filter_DSTATE += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S2347>/Filter' */
    rtDW.Filter_DSTATE_d += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S2352>/Integrator' incorporates:
     *  Gain: '<S2349>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_b += rtP.ANG_A_I_CH2_1 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S16>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S16>/Switch Case' */

  /* SwitchCase: '<S2>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status10'
   */
  switch ((int32_T)rtU.yaw_status10) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S2>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S167>/Action Port'
     */
    /* Sum: '<S167>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm10'
     *  Inport: '<Root>/yaw_target10'
     */
    rtb_Sum_is = rtU.yaw_target10 - rtU.yaw_speed_rpm10;

    /* Gain: '<S204>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S196>/Filter'
     *  Gain: '<S195>/Derivative Gain'
     *  Sum: '<S196>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH2_2 * rtb_Sum_is -
      rtDW.Filter_DSTATE_fg) * 100.0F;

    /* Sum: '<S210>/Sum' incorporates:
     *  DiscreteIntegrator: '<S201>/Integrator'
     *  Gain: '<S206>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_2 * rtb_Sum_is + rtDW.Integrator_DSTATE_kh) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S208>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT10' */
      rtY.yaw_SPD_OUT10 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT10' */
      rtY.yaw_SPD_OUT10 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT10' */
      rtY.yaw_SPD_OUT10 = u0;
    }

    /* End of Saturate: '<S208>/Saturation' */

    /* Update for DiscreteIntegrator: '<S196>/Filter' */
    rtDW.Filter_DSTATE_fg += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S201>/Integrator' incorporates:
     *  Gain: '<S198>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_kh += rtP.SPD_I_CH2_2 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S2>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S2>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S168>/Action Port'
     */
    /* Sum: '<S168>/Sum' incorporates:
     *  Gain: '<S168>/Gain'
     *  Inport: '<Root>/yaw_circle10'
     *  Inport: '<Root>/yaw_ecd10'
     *  Inport: '<Root>/yaw_target10'
     *  Sum: '<S168>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target10 - (8191.0F * rtU.yaw_circle10 +
      rtU.yaw_ecd10);

    /* Abs: '<S168>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S168>/Switch2' incorporates:
     *  Constant: '<S168>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH2_2)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S168>/Switch2' */

    /* Gain: '<S303>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S295>/Filter'
     *  Gain: '<S294>/Derivative Gain'
     *  Sum: '<S295>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH2_2 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_l4) * 100.0F;

    /* Switch: '<S168>/Switch1' incorporates:
     *  Constant: '<S168>/Constant'
     *  Gain: '<S168>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm10'
     *  Saturate: '<S307>/Saturation'
     *  Sum: '<S168>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH2_2) {
      /* Sum: '<S309>/Sum' incorporates:
       *  DiscreteIntegrator: '<S300>/Integrator'
       *  Gain: '<S305>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH2_2 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_nu) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S307>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH2_2 * u0 - rtU.yaw_speed_rpm10;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S168>/Switch1' */

    /* Gain: '<S255>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S247>/Filter'
     *  Gain: '<S246>/Derivative Gain'
     *  Sum: '<S247>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH2_2 * rtb_Sum_is -
      rtDW.Filter_DSTATE_li) * 100.0F;

    /* Sum: '<S261>/Sum' incorporates:
     *  DiscreteIntegrator: '<S252>/Integrator'
     *  Gain: '<S257>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH2_2 * rtb_Sum_is + rtDW.Integrator_DSTATE_c) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S259>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT10' */
      rtY.yaw_ANG_OUT10 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT10' */
      rtY.yaw_ANG_OUT10 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT10' */
      rtY.yaw_ANG_OUT10 = u0;
    }

    /* End of Saturate: '<S259>/Saturation' */

    /* Chart: '<S168>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd10'
     *  Inport: '<Root>/yaw_last_ecd10'
     *  Sum: '<S168>/Sum3'
     */
    Chart1(rtU.yaw_ecd10 - rtU.yaw_last_ecd10, &rtDW.u2_gk, &rtDW.sf_Chart1_f);

    /* Outport: '<Root>/yaw_circle_out10' incorporates:
     *  Inport: '<Root>/yaw_circle10'
     *  Sum: '<S168>/Sum4'
     */
    rtY.yaw_circle_out10 = rtDW.u2_gk + rtU.yaw_circle10;

    /* Update for DiscreteIntegrator: '<S300>/Integrator' incorporates:
     *  Gain: '<S297>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_nu += rtP.ANG_S_I_CH2_2 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S295>/Filter' */
    rtDW.Filter_DSTATE_l4 += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S247>/Filter' */
    rtDW.Filter_DSTATE_li += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S252>/Integrator' incorporates:
     *  Gain: '<S249>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_c += rtP.ANG_A_I_CH2_2 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S2>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S2>/Switch Case' */

  /* SwitchCase: '<S3>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status11'
   */
  switch ((int32_T)rtU.yaw_status11) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S3>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S317>/Action Port'
     */
    /* Sum: '<S317>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm11'
     *  Inport: '<Root>/yaw_target11'
     */
    rtb_Sum_is = rtU.yaw_target11 - rtU.yaw_speed_rpm11;

    /* Gain: '<S354>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S346>/Filter'
     *  Gain: '<S345>/Derivative Gain'
     *  Sum: '<S346>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH2_3 * rtb_Sum_is -
      rtDW.Filter_DSTATE_aa) * 100.0F;

    /* Sum: '<S360>/Sum' incorporates:
     *  DiscreteIntegrator: '<S351>/Integrator'
     *  Gain: '<S356>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_3 * rtb_Sum_is + rtDW.Integrator_DSTATE_ij) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S358>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT11' */
      rtY.yaw_SPD_OUT11 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT11' */
      rtY.yaw_SPD_OUT11 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT11' */
      rtY.yaw_SPD_OUT11 = u0;
    }

    /* End of Saturate: '<S358>/Saturation' */

    /* Update for DiscreteIntegrator: '<S346>/Filter' */
    rtDW.Filter_DSTATE_aa += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S351>/Integrator' incorporates:
     *  Gain: '<S348>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ij += rtP.SPD_I_CH2_3 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S3>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S3>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S318>/Action Port'
     */
    /* Sum: '<S318>/Sum' incorporates:
     *  Gain: '<S318>/Gain'
     *  Inport: '<Root>/yaw_circle11'
     *  Inport: '<Root>/yaw_ecd11'
     *  Inport: '<Root>/yaw_target11'
     *  Sum: '<S318>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target11 - (8191.0F * rtU.yaw_circle11 +
      rtU.yaw_ecd11);

    /* Abs: '<S318>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S318>/Switch2' incorporates:
     *  Constant: '<S318>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH2_3)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S318>/Switch2' */

    /* Gain: '<S453>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S445>/Filter'
     *  Gain: '<S444>/Derivative Gain'
     *  Sum: '<S445>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH2_3 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_np) * 100.0F;

    /* Switch: '<S318>/Switch1' incorporates:
     *  Constant: '<S318>/Constant'
     *  Gain: '<S318>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm11'
     *  Saturate: '<S457>/Saturation'
     *  Sum: '<S318>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH2_3) {
      /* Sum: '<S459>/Sum' incorporates:
       *  DiscreteIntegrator: '<S450>/Integrator'
       *  Gain: '<S455>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH2_3 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_if) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S457>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH2_3 * u0 - rtU.yaw_speed_rpm11;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S318>/Switch1' */

    /* Gain: '<S405>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S397>/Filter'
     *  Gain: '<S396>/Derivative Gain'
     *  Sum: '<S397>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH2_3 * rtb_Sum_is -
      rtDW.Filter_DSTATE_lb) * 100.0F;

    /* Sum: '<S411>/Sum' incorporates:
     *  DiscreteIntegrator: '<S402>/Integrator'
     *  Gain: '<S407>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH2_3 * rtb_Sum_is + rtDW.Integrator_DSTATE_it) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S409>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT11' */
      rtY.yaw_ANG_OUT11 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT11' */
      rtY.yaw_ANG_OUT11 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT11' */
      rtY.yaw_ANG_OUT11 = u0;
    }

    /* End of Saturate: '<S409>/Saturation' */

    /* Chart: '<S318>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd11'
     *  Inport: '<Root>/yaw_last_ecd11'
     *  Sum: '<S318>/Sum3'
     */
    Chart1(rtU.yaw_ecd11 - rtU.yaw_last_ecd11, &rtDW.u2_a, &rtDW.sf_Chart1_i);

    /* Outport: '<Root>/yaw_circle_out11' incorporates:
     *  Inport: '<Root>/yaw_circle11'
     *  Sum: '<S318>/Sum4'
     */
    rtY.yaw_circle_out11 = rtDW.u2_a + rtU.yaw_circle11;

    /* Update for DiscreteIntegrator: '<S450>/Integrator' incorporates:
     *  Gain: '<S447>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_if += rtP.ANG_S_I_CH2_3 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S445>/Filter' */
    rtDW.Filter_DSTATE_np += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S397>/Filter' */
    rtDW.Filter_DSTATE_lb += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S402>/Integrator' incorporates:
     *  Gain: '<S399>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_it += rtP.ANG_A_I_CH2_3 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S3>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S3>/Switch Case' */

  /* SwitchCase: '<S4>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status12'
   */
  switch ((int32_T)rtU.yaw_status12) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S4>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S467>/Action Port'
     */
    /* Sum: '<S467>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm12'
     *  Inport: '<Root>/yaw_target12'
     */
    rtb_Sum_is = rtU.yaw_target12 - rtU.yaw_speed_rpm12;

    /* Gain: '<S504>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S496>/Filter'
     *  Gain: '<S495>/Derivative Gain'
     *  Sum: '<S496>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH2_4 * rtb_Sum_is -
      rtDW.Filter_DSTATE_b) * 100.0F;

    /* Sum: '<S510>/Sum' incorporates:
     *  DiscreteIntegrator: '<S501>/Integrator'
     *  Gain: '<S506>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_4 * rtb_Sum_is + rtDW.Integrator_DSTATE_kf) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S508>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT12' */
      rtY.yaw_SPD_OUT12 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT12' */
      rtY.yaw_SPD_OUT12 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT12' */
      rtY.yaw_SPD_OUT12 = u0;
    }

    /* End of Saturate: '<S508>/Saturation' */

    /* Update for DiscreteIntegrator: '<S496>/Filter' */
    rtDW.Filter_DSTATE_b += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S501>/Integrator' incorporates:
     *  Gain: '<S498>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_kf += rtP.SPD_I_CH2_4 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S4>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S4>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S468>/Action Port'
     */
    /* Sum: '<S468>/Sum' incorporates:
     *  Gain: '<S468>/Gain'
     *  Inport: '<Root>/yaw_circle12'
     *  Inport: '<Root>/yaw_ecd12'
     *  Inport: '<Root>/yaw_target12'
     *  Sum: '<S468>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target12 - (8191.0F * rtU.yaw_circle12 +
      rtU.yaw_ecd12);

    /* Abs: '<S468>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S468>/Switch2' incorporates:
     *  Constant: '<S468>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH2_4)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S468>/Switch2' */

    /* Gain: '<S603>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S595>/Filter'
     *  Gain: '<S594>/Derivative Gain'
     *  Sum: '<S595>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH2_4 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_cq) * 100.0F;

    /* Switch: '<S468>/Switch1' incorporates:
     *  Constant: '<S468>/Constant'
     *  Gain: '<S468>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm12'
     *  Saturate: '<S607>/Saturation'
     *  Sum: '<S468>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH2_4) {
      /* Sum: '<S609>/Sum' incorporates:
       *  DiscreteIntegrator: '<S600>/Integrator'
       *  Gain: '<S605>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH2_4 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_el) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S607>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH2_4 * u0 - rtU.yaw_speed_rpm12;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S468>/Switch1' */

    /* Gain: '<S555>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S547>/Filter'
     *  Gain: '<S546>/Derivative Gain'
     *  Sum: '<S547>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH2_4 * rtb_Sum_is -
      rtDW.Filter_DSTATE_js) * 100.0F;

    /* Sum: '<S561>/Sum' incorporates:
     *  DiscreteIntegrator: '<S552>/Integrator'
     *  Gain: '<S557>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH2_4 * rtb_Sum_is + rtDW.Integrator_DSTATE_mp) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S559>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT12' */
      rtY.yaw_ANG_OUT12 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT12' */
      rtY.yaw_ANG_OUT12 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT12' */
      rtY.yaw_ANG_OUT12 = u0;
    }

    /* End of Saturate: '<S559>/Saturation' */

    /* Chart: '<S468>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd12'
     *  Inport: '<Root>/yaw_last_ecd12'
     *  Sum: '<S468>/Sum3'
     */
    Chart1(rtU.yaw_ecd12 - rtU.yaw_last_ecd12, &rtDW.u2_f3, &rtDW.sf_Chart1_o);

    /* Outport: '<Root>/yaw_circle_out12' incorporates:
     *  Inport: '<Root>/yaw_circle12'
     *  Sum: '<S468>/Sum4'
     */
    rtY.yaw_circle_out12 = rtDW.u2_f3 + rtU.yaw_circle12;

    /* Update for DiscreteIntegrator: '<S600>/Integrator' incorporates:
     *  Gain: '<S597>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_el += rtP.ANG_S_I_CH2_4 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S595>/Filter' */
    rtDW.Filter_DSTATE_cq += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S547>/Filter' */
    rtDW.Filter_DSTATE_js += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S552>/Integrator' incorporates:
     *  Gain: '<S549>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_mp += rtP.ANG_A_I_CH2_4 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S4>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S4>/Switch Case' */

  /* SwitchCase: '<S5>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status13'
   */
  switch ((int32_T)rtU.yaw_status13) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S5>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S617>/Action Port'
     */
    /* Sum: '<S617>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm13'
     *  Inport: '<Root>/yaw_target13'
     */
    rtb_Sum_is = rtU.yaw_target13 - rtU.yaw_speed_rpm13;

    /* Gain: '<S654>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S646>/Filter'
     *  Gain: '<S645>/Derivative Gain'
     *  Sum: '<S646>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH2_5 * rtb_Sum_is -
      rtDW.Filter_DSTATE_gl) * 100.0F;

    /* Sum: '<S660>/Sum' incorporates:
     *  DiscreteIntegrator: '<S651>/Integrator'
     *  Gain: '<S656>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_5 * rtb_Sum_is + rtDW.Integrator_DSTATE_ez) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S658>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT13' */
      rtY.yaw_SPD_OUT13 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT13' */
      rtY.yaw_SPD_OUT13 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT13' */
      rtY.yaw_SPD_OUT13 = u0;
    }

    /* End of Saturate: '<S658>/Saturation' */

    /* Update for DiscreteIntegrator: '<S646>/Filter' */
    rtDW.Filter_DSTATE_gl += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S651>/Integrator' incorporates:
     *  Gain: '<S648>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ez += rtP.SPD_I_CH2_5 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S5>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S5>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S618>/Action Port'
     */
    /* Sum: '<S618>/Sum' incorporates:
     *  Gain: '<S618>/Gain'
     *  Inport: '<Root>/yaw_circle13'
     *  Inport: '<Root>/yaw_ecd13'
     *  Inport: '<Root>/yaw_target13'
     *  Sum: '<S618>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target13 - (8191.0F * rtU.yaw_circle13 +
      rtU.yaw_ecd13);

    /* Abs: '<S618>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S618>/Switch2' incorporates:
     *  Constant: '<S618>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH2_5)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S618>/Switch2' */

    /* Gain: '<S753>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S745>/Filter'
     *  Gain: '<S744>/Derivative Gain'
     *  Sum: '<S745>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH2_5 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_kk) * 100.0F;

    /* Switch: '<S618>/Switch1' incorporates:
     *  Constant: '<S618>/Constant'
     *  Gain: '<S618>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm13'
     *  Saturate: '<S757>/Saturation'
     *  Sum: '<S618>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH2_5) {
      /* Sum: '<S759>/Sum' incorporates:
       *  DiscreteIntegrator: '<S750>/Integrator'
       *  Gain: '<S755>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH2_5 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_fr) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S757>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH2_5 * u0 - rtU.yaw_speed_rpm13;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S618>/Switch1' */

    /* Gain: '<S705>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S697>/Filter'
     *  Gain: '<S696>/Derivative Gain'
     *  Sum: '<S697>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH2_5 * rtb_Sum_is -
      rtDW.Filter_DSTATE_iz) * 100.0F;

    /* Sum: '<S711>/Sum' incorporates:
     *  DiscreteIntegrator: '<S702>/Integrator'
     *  Gain: '<S707>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH2_5 * rtb_Sum_is + rtDW.Integrator_DSTATE_ml) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S709>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT13' */
      rtY.yaw_ANG_OUT13 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT13' */
      rtY.yaw_ANG_OUT13 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT13' */
      rtY.yaw_ANG_OUT13 = u0;
    }

    /* End of Saturate: '<S709>/Saturation' */

    /* Chart: '<S618>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd13'
     *  Inport: '<Root>/yaw_last_ecd13'
     *  Sum: '<S618>/Sum3'
     */
    Chart1(rtU.yaw_ecd13 - rtU.yaw_last_ecd13, &rtDW.u2_d4, &rtDW.sf_Chart1_ff);

    /* Outport: '<Root>/yaw_circle_out13' incorporates:
     *  Inport: '<Root>/yaw_circle13'
     *  Sum: '<S618>/Sum4'
     */
    rtY.yaw_circle_out13 = rtDW.u2_d4 + rtU.yaw_circle13;

    /* Update for DiscreteIntegrator: '<S750>/Integrator' incorporates:
     *  Gain: '<S747>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_fr += rtP.ANG_S_I_CH2_5 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S745>/Filter' */
    rtDW.Filter_DSTATE_kk += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S697>/Filter' */
    rtDW.Filter_DSTATE_iz += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S702>/Integrator' incorporates:
     *  Gain: '<S699>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ml += rtP.ANG_A_I_CH2_5 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S5>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S5>/Switch Case' */

  /* SwitchCase: '<S6>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status14'
   */
  switch ((int32_T)rtU.yaw_status14) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S6>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S767>/Action Port'
     */
    /* Sum: '<S767>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm14'
     *  Inport: '<Root>/yaw_target14'
     */
    rtb_Sum_is = rtU.yaw_target14 - rtU.yaw_speed_rpm14;

    /* Gain: '<S804>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S796>/Filter'
     *  Gain: '<S795>/Derivative Gain'
     *  Sum: '<S796>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH2_6 * rtb_Sum_is -
      rtDW.Filter_DSTATE_o) * 100.0F;

    /* Sum: '<S810>/Sum' incorporates:
     *  DiscreteIntegrator: '<S801>/Integrator'
     *  Gain: '<S806>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_6 * rtb_Sum_is + rtDW.Integrator_DSTATE_ek) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S808>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT14' */
      rtY.yaw_SPD_OUT14 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT14' */
      rtY.yaw_SPD_OUT14 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT14' */
      rtY.yaw_SPD_OUT14 = u0;
    }

    /* End of Saturate: '<S808>/Saturation' */

    /* Update for DiscreteIntegrator: '<S796>/Filter' */
    rtDW.Filter_DSTATE_o += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S801>/Integrator' incorporates:
     *  Gain: '<S798>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ek += rtP.SPD_I_CH2_6 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S6>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S6>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S768>/Action Port'
     */
    /* Sum: '<S768>/Sum' incorporates:
     *  Gain: '<S768>/Gain'
     *  Inport: '<Root>/yaw_circle14'
     *  Inport: '<Root>/yaw_ecd14'
     *  Inport: '<Root>/yaw_target14'
     *  Sum: '<S768>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target14 - (8191.0F * rtU.yaw_circle14 +
      rtU.yaw_ecd14);

    /* Abs: '<S768>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S768>/Switch2' incorporates:
     *  Constant: '<S768>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH2_6)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S768>/Switch2' */

    /* Gain: '<S903>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S895>/Filter'
     *  Gain: '<S894>/Derivative Gain'
     *  Sum: '<S895>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH2_6 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_di) * 100.0F;

    /* Switch: '<S768>/Switch1' incorporates:
     *  Constant: '<S768>/Constant'
     *  Gain: '<S768>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm14'
     *  Saturate: '<S907>/Saturation'
     *  Sum: '<S768>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH2_6) {
      /* Sum: '<S909>/Sum' incorporates:
       *  DiscreteIntegrator: '<S900>/Integrator'
       *  Gain: '<S905>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH2_6 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_n5) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S907>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH2_6 * u0 - rtU.yaw_speed_rpm14;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S768>/Switch1' */

    /* Gain: '<S855>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S847>/Filter'
     *  Gain: '<S846>/Derivative Gain'
     *  Sum: '<S847>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH2_6 * rtb_Sum_is -
      rtDW.Filter_DSTATE_g5) * 100.0F;

    /* Sum: '<S861>/Sum' incorporates:
     *  DiscreteIntegrator: '<S852>/Integrator'
     *  Gain: '<S857>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH2_6 * rtb_Sum_is + rtDW.Integrator_DSTATE_ll) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S859>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT14' */
      rtY.yaw_ANG_OUT14 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT14' */
      rtY.yaw_ANG_OUT14 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT14' */
      rtY.yaw_ANG_OUT14 = u0;
    }

    /* End of Saturate: '<S859>/Saturation' */

    /* Chart: '<S768>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd14'
     *  Inport: '<Root>/yaw_last_ecd14'
     *  Sum: '<S768>/Sum3'
     */
    Chart1(rtU.yaw_ecd14 - rtU.yaw_last_ecd14, &rtDW.u2_gc, &rtDW.sf_Chart1_b);

    /* Outport: '<Root>/yaw_circle_out14' incorporates:
     *  Inport: '<Root>/yaw_circle14'
     *  Sum: '<S768>/Sum4'
     */
    rtY.yaw_circle_out14 = rtDW.u2_gc + rtU.yaw_circle14;

    /* Update for DiscreteIntegrator: '<S900>/Integrator' incorporates:
     *  Gain: '<S897>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_n5 += rtP.ANG_S_I_CH2_6 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S895>/Filter' */
    rtDW.Filter_DSTATE_di += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S847>/Filter' */
    rtDW.Filter_DSTATE_g5 += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S852>/Integrator' incorporates:
     *  Gain: '<S849>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ll += rtP.ANG_A_I_CH2_6 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S6>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S6>/Switch Case' */

  /* SwitchCase: '<S7>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_status15'
   */
  switch ((int32_T)rtU.yaw_status15) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S7>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S917>/Action Port'
     */
    /* Sum: '<S917>/Sum' incorporates:
     *  Inport: '<Root>/yaw_speed_rpm15'
     *  Inport: '<Root>/yaw_target15'
     */
    rtb_Sum_is = rtU.yaw_target15 - rtU.yaw_speed_rpm15;

    /* Gain: '<S954>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S946>/Filter'
     *  Gain: '<S945>/Derivative Gain'
     *  Sum: '<S946>/SumD'
     */
    rtb_FilterCoefficient_ce = (rtP.SPD_D_CH2_7 * rtb_Sum_is -
      rtDW.Filter_DSTATE_pp) * 100.0F;

    /* Sum: '<S960>/Sum' incorporates:
     *  DiscreteIntegrator: '<S951>/Integrator'
     *  Gain: '<S956>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_7 * rtb_Sum_is + rtDW.Integrator_DSTATE_by) +
      rtb_FilterCoefficient_ce;

    /* Saturate: '<S958>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT15' */
      rtY.yaw_SPD_OUT15 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_SPD_OUT15' */
      rtY.yaw_SPD_OUT15 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_SPD_OUT15' */
      rtY.yaw_SPD_OUT15 = u0;
    }

    /* End of Saturate: '<S958>/Saturation' */

    /* Update for DiscreteIntegrator: '<S946>/Filter' */
    rtDW.Filter_DSTATE_pp += 0.001F * rtb_FilterCoefficient_ce;

    /* Update for DiscreteIntegrator: '<S951>/Integrator' incorporates:
     *  Gain: '<S948>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_by += rtP.SPD_I_CH2_7 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S7>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S7>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S918>/Action Port'
     */
    /* Sum: '<S918>/Sum' incorporates:
     *  Gain: '<S918>/Gain'
     *  Inport: '<Root>/yaw_circle15'
     *  Inport: '<Root>/yaw_ecd15'
     *  Inport: '<Root>/yaw_target15'
     *  Sum: '<S918>/Sum2'
     */
    rtb_FilterCoefficient_ce = rtU.yaw_target15 - (8191.0F * rtU.yaw_circle15 +
      rtU.yaw_ecd15);

    /* Abs: '<S918>/Abs' */
    rtb_Sum_is = (real32_T)fabs(rtb_FilterCoefficient_ce);

    /* Switch: '<S918>/Switch2' incorporates:
     *  Constant: '<S918>/Constant'
     */
    if (!(rtb_Sum_is > rtP.DEADBAND_CH2_7)) {
      rtb_FilterCoefficient_ce = 0.0F;
    }

    /* End of Switch: '<S918>/Switch2' */

    /* Gain: '<S1053>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1045>/Filter'
     *  Gain: '<S1044>/Derivative Gain'
     *  Sum: '<S1045>/SumD'
     */
    rtb_FilterCoefficient_ga = (rtP.ANG_S_D_CH2_7 * rtb_FilterCoefficient_ce -
      rtDW.Filter_DSTATE_lg) * 100.0F;

    /* Switch: '<S918>/Switch1' incorporates:
     *  Constant: '<S918>/Constant'
     *  Gain: '<S918>/Multiply'
     *  Inport: '<Root>/yaw_speed_rpm15'
     *  Saturate: '<S1057>/Saturation'
     *  Sum: '<S918>/Sum1'
     */
    if (rtb_Sum_is > rtP.DEADBAND_CH2_7) {
      /* Sum: '<S1059>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1050>/Integrator'
       *  Gain: '<S1055>/Proportional Gain'
       */
      u0 = (rtP.ANG_S_P_CH2_7 * rtb_FilterCoefficient_ce +
            rtDW.Integrator_DSTATE_nj) + rtb_FilterCoefficient_ga;

      /* Saturate: '<S1057>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_is = rtP.TRANS_CH2_7 * u0 - rtU.yaw_speed_rpm15;
    } else {
      rtb_Sum_is = 0.0F;
    }

    /* End of Switch: '<S918>/Switch1' */

    /* Gain: '<S1005>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S997>/Filter'
     *  Gain: '<S996>/Derivative Gain'
     *  Sum: '<S997>/SumD'
     */
    rtb_FilterCoefficient_j4 = (rtP.ANG_A_D_CH2_7 * rtb_Sum_is -
      rtDW.Filter_DSTATE_cr) * 100.0F;

    /* Sum: '<S1011>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1002>/Integrator'
     *  Gain: '<S1007>/Proportional Gain'
     */
    u0 = (rtP.ANG_A_P_CH2_7 * rtb_Sum_is + rtDW.Integrator_DSTATE_ep) +
      rtb_FilterCoefficient_j4;

    /* Saturate: '<S1009>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT15' */
      rtY.yaw_ANG_OUT15 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/yaw_ANG_OUT15' */
      rtY.yaw_ANG_OUT15 = -16384.0F;
    } else {
      /* Outport: '<Root>/yaw_ANG_OUT15' */
      rtY.yaw_ANG_OUT15 = u0;
    }

    /* End of Saturate: '<S1009>/Saturation' */

    /* Chart: '<S918>/Chart1' incorporates:
     *  Inport: '<Root>/yaw_ecd15'
     *  Inport: '<Root>/yaw_last_ecd15'
     *  Sum: '<S918>/Sum3'
     */
    Chart1(rtU.yaw_ecd15 - rtU.yaw_last_ecd15, &rtDW.u2_c, &rtDW.sf_Chart1_g);

    /* Outport: '<Root>/yaw_circle_out15' incorporates:
     *  Inport: '<Root>/yaw_circle15'
     *  Sum: '<S918>/Sum4'
     */
    rtY.yaw_circle_out15 = rtDW.u2_c + rtU.yaw_circle15;

    /* Update for DiscreteIntegrator: '<S1050>/Integrator' incorporates:
     *  Gain: '<S1047>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_nj += rtP.ANG_S_I_CH2_7 * rtb_FilterCoefficient_ce *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1045>/Filter' */
    rtDW.Filter_DSTATE_lg += 0.001F * rtb_FilterCoefficient_ga;

    /* Update for DiscreteIntegrator: '<S997>/Filter' */
    rtDW.Filter_DSTATE_cr += 0.001F * rtb_FilterCoefficient_j4;

    /* Update for DiscreteIntegrator: '<S1002>/Integrator' incorporates:
     *  Gain: '<S999>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ep += rtP.ANG_A_I_CH2_7 * rtb_Sum_is * 0.001F;

    /* End of Outputs for SubSystem: '<S7>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S7>/Switch Case' */
}

/* Model initialize function */
void pidctl_initialize(void)
{
  /* SystemInitialize for IfAction SubSystem: '<S8>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S1068>/Chart1' */
  Chart1_Init(&rtDW.u2_i);

  /* End of SystemInitialize for SubSystem: '<S8>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S1>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S18>/Chart1' */
  Chart1_Init(&rtDW.u2_e);

  /* End of SystemInitialize for SubSystem: '<S1>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S1218>/Chart1' */
  Chart1_Init(&rtDW.u2_gr);

  /* End of SystemInitialize for SubSystem: '<S9>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S10>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S1368>/Chart1' */
  Chart1_Init(&rtDW.u2_g);

  /* End of SystemInitialize for SubSystem: '<S10>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S11>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S1518>/Chart1' */
  Chart1_Init(&rtDW.u2_f);

  /* End of SystemInitialize for SubSystem: '<S11>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S12>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S1668>/Chart1' */
  Chart1_Init(&rtDW.u2_b);

  /* End of SystemInitialize for SubSystem: '<S12>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S13>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S1818>/Chart1' */
  Chart1_Init(&rtDW.u2_l);

  /* End of SystemInitialize for SubSystem: '<S13>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S14>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S1968>/Chart1' */
  Chart1_Init(&rtDW.u2_n);

  /* End of SystemInitialize for SubSystem: '<S14>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S15>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S2118>/Chart1' */
  Chart1_Init(&rtDW.u2_d);

  /* End of SystemInitialize for SubSystem: '<S15>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S16>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S2268>/Chart1' */
  Chart1_Init(&rtDW.u2);

  /* End of SystemInitialize for SubSystem: '<S16>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S2>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S168>/Chart1' */
  Chart1_Init(&rtDW.u2_gk);

  /* End of SystemInitialize for SubSystem: '<S2>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S3>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S318>/Chart1' */
  Chart1_Init(&rtDW.u2_a);

  /* End of SystemInitialize for SubSystem: '<S3>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S4>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S468>/Chart1' */
  Chart1_Init(&rtDW.u2_f3);

  /* End of SystemInitialize for SubSystem: '<S4>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S5>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S618>/Chart1' */
  Chart1_Init(&rtDW.u2_d4);

  /* End of SystemInitialize for SubSystem: '<S5>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S6>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S768>/Chart1' */
  Chart1_Init(&rtDW.u2_gc);

  /* End of SystemInitialize for SubSystem: '<S6>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S7>/If Action_speed Subsystem1' */

  /* SystemInitialize for Chart: '<S918>/Chart1' */
  Chart1_Init(&rtDW.u2_c);

  /* End of SystemInitialize for SubSystem: '<S7>/If Action_speed Subsystem1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

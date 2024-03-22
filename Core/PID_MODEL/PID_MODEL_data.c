/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PID_MODEL_data.c
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

/* Block parameters (default storage) */
P rtP = {
  /* Variable: DeadBand
   * Referenced by:
   *   '<S4>/Switch1'
   *   '<S4>/Switch2'
   *   '<S154>/Switch1'
   *   '<S154>/Switch2'
   */
  500.0,

  /* Variable: Kd_a
   * Referenced by: '<S130>/Derivative Gain'
   */
  0.0,

  /* Variable: Kd_a_1
   * Referenced by: '<S280>/Derivative Gain'
   */
  0.0,

  /* Variable: Kd_s
   * Referenced by:
   *   '<S31>/Derivative Gain'
   *   '<S82>/Derivative Gain'
   */
  0.0,

  /* Variable: Kd_s_1
   * Referenced by:
   *   '<S181>/Derivative Gain'
   *   '<S232>/Derivative Gain'
   */
  0.0,

  /* Variable: Ki_a
   * Referenced by: '<S133>/Integral Gain'
   */
  0.0,

  /* Variable: Ki_a_1
   * Referenced by: '<S283>/Integral Gain'
   */
  0.0,

  /* Variable: Ki_s
   * Referenced by:
   *   '<S34>/Integral Gain'
   *   '<S85>/Integral Gain'
   */
  0.0,

  /* Variable: Ki_s_1
   * Referenced by:
   *   '<S184>/Integral Gain'
   *   '<S235>/Integral Gain'
   */
  0.0,

  /* Variable: Kp_a
   * Referenced by: '<S141>/Proportional Gain'
   */
  0.0,

  /* Variable: Kp_a_1
   * Referenced by: '<S291>/Proportional Gain'
   */
  0.0,

  /* Variable: Kp_s
   * Referenced by:
   *   '<S42>/Proportional Gain'
   *   '<S93>/Proportional Gain'
   */
  0.0,

  /* Variable: Kp_s_1
   * Referenced by:
   *   '<S192>/Proportional Gain'
   *   '<S243>/Proportional Gain'
   */
  0.0,

  /* Variable: trans
   * Referenced by:
   *   '<S4>/Multiply'
   *   '<S154>/Multiply'
   */
  0.5
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

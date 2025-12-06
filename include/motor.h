#ifndef MOTOR_H
#define MOTOR_H

/**
 * Turns the motor on
 */
void motor_on();

/**
 * Turns the motor off
 */
void motor_off();

/**
 * Is called after the motor is turned on
 */
void motor_turned_on();

/**
 * Is called after the motor is turned doff
 */
void motor_turned_off();

#endif

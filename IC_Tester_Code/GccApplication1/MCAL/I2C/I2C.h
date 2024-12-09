/*
 * I2C.h
 *
 * Created: 5/18/2024 6:22:44 PM
 *  Author: Blu-Ray
 *  
 *  Description:
 *  This file contains the function prototypes and necessary definitions for 
 *  interfacing with I2C (Inter-Integrated Circuit) hardware. It provides 
 *  initialization routines and functions for starting communication, 
 *  writing data, reading data, and stopping communication over the I2C bus.
 */

#ifndef I2C_H_
#define I2C_H_

#include "StdTypes.h"
#include "MemoryMap.h"

/**
 * @brief I2C clock frequency in kHz.
 */
#define SCL_CLK ((u8)(1E5))

/**
 * @enum I2C_retStatus_t
 * @brief Return status of I2C functions.
 */
typedef enum {
	I2C_START_FAILED,    /**< I2C start condition failed */
	I2C_ACK_RECEIVED,    /**< Acknowledgment received */
	I2C_NACK_RECEIVED,   /**< No acknowledgment received */
	I2C_TRANS_FAILURE    /**< I2C transmission failure */
} I2C_retStatus_t;

/**
 * @brief Initializes the I2C peripheral.
 *
 * Configures the I2C clock frequency and sets up the necessary hardware
 * registers to enable I2C communication.
 */
void I2C_Init(void);

/**
 * @brief Sends a start condition followed by the write address.
 *
 * @param write_address The 7-bit address of the I2C slave with the R/W bit.
 * @return I2C_retStatus_t Status of the start condition and address transmission.
 */
I2C_retStatus_t I2C_Start(u8 write_address);

/**
 * @brief Sends a repeated start condition followed by the read address.
 *
 * @param read_address The 7-bit address of the I2C slave with the R/W bit.
 * @return I2C_retStatus_t Status of the repeated start condition.
 */
I2C_retStatus_t I2C_Repeated_Start(u8 read_address);

/**
 * @brief Writes a byte of data to the I2C bus.
 *
 * @param data The data byte to be transmitted.
 * @return I2C_retStatus_t Status of the data transmission.
 */
I2C_retStatus_t I2C_Write(u8 data);

/**
 * @brief Reads a byte of data from the I2C bus and sends an acknowledgment.
 *
 * @return u8 The data byte received from the I2C slave.
 */
u8 I2C_Read_Ack(void);

/**
 * @brief Reads a byte of data from the I2C bus without sending an acknowledgment.
 *
 * @return u8 The data byte received from the I2C slave.
 */
u8 I2C_Read_Nack(void);

/**
 * @brief Sends a stop condition to terminate the I2C communication.
 */
void I2C_Stop(void);

#endif /* I2C_H_ */

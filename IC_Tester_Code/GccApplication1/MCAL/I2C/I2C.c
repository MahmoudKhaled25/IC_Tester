/*
 * I2C.c
 *
 * Created: 5/18/2024 6:22:57 PM
 *  Author: Blu-Ray
 */ 

#include <math.h>
#define F_CPU	((u8)(8E6))
#include "I2C.h"

/* Define bit rate */
#define PRESCALER_MASK			(0xF8)
#define ST_CON_SUCCESS			(0x08)
#define ST_SLAW_ACK				(0x18)
#define ST_SLAW_NACK			(0x20)
#define REPST_CON_SUCCESS		(0x10)
#define REPST_SLAW_ACK			(0x40)
#define REPST_SLAW_NACK			(0x48)
#define WRITE_ACK				(0x28)
#define WRITE_NACK				(0x30)

#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

void I2C_Init(void)			/* I2C initialize function */
{
	TWBR = BITRATE(0x00);	/* Get bit rate register value by formula */
}


I2C_retStatus_t I2C_Start(u8 write_address)/* I2C start function */
{
	u8 status;								/* Declare variable */
	
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);	/* Enable TWI, generate START */
	
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job */
	
	status=TWSR&PRESCALER_MASK;				/* Read TWI status register */
	if(status!=ST_CON_SUCCESS)			/* Check weather START transmitted or not? */
		return I2C_START_FAILED;			/* Return 0 to indicate start condition fail */
		
	TWDR=write_address;						/* Write SLA+W in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);				/* Enable TWI & clear interrupt flag */
	
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job */
	
	status=TWSR&PRESCALER_MASK;				/* Read TWI status register */
	if(status==ST_SLAW_ACK)					/* Check for SLA+W transmitted & ack received */
		return I2C_ACK_RECEIVED;			/* To indicate ack received */
	else if(status==ST_SLAW_NACK)				/* Check for SLA+W transmitted & nack received */
		return I2C_NACK_RECEIVED;			/* To indicate nack received */
	else
		return I2C_TRANS_FAILURE;			/* To indicate SLA+W failed */
}


I2C_retStatus_t I2C_Repeated_Start(u8 read_address) /* I2C repeated start function */
{
	u8 status;								/* Declare variable */
	
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);	/* Enable TWI, generate start */
	
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job */
	
	status=TWSR&PRESCALER_MASK;				/* Read TWI status register */
	if(status!=REPST_CON_SUCCESS)		/* Check for repeated start transmitted */
		return I2C_START_FAILED;			/* Return 0 for repeated start condition fail */
		
	TWDR=read_address;						/* Write SLA+R in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);				/* Enable TWI and clear interrupt flag */
	
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job */
	
	status=TWSR&PRESCALER_MASK;				/* Read TWI status register */
	if(status==REPST_SLAW_ACK)				/* Check for SLA+R transmitted & ack received */
		return I2C_ACK_RECEIVED;			/* Return 1 to indicate ack received */
	else if(status==REPST_SLAW_ACK)			/* Check for SLA+R transmitted &nack received */
		return I2C_NACK_RECEIVED;			/* Return 2 to indicate nack received */
	else
		return I2C_TRANS_FAILURE;			/* To indicate SLA+W failed */
}

I2C_retStatus_t I2C_Write(u8 data)	/* I2C write function */
{
	u8 status;						/* Declare variable */
	
	TWDR=data;						/* Copy data in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);		/* Enable TWI and clear interrupt flag */
	
	while(!(TWCR&(1<<TWINT)));		/* Wait until TWI finish its current job */
	
	status=TWSR&PRESCALER_MASK;		/* Read TWI status register */
	if(status==WRITE_ACK)			/* Check for data transmitted & ack received */
		return I2C_ACK_RECEIVED;	/* To indicate ack received */
	else if(status==WRITE_NACK)		/* Check for data transmitted & nack received */
		return I2C_NACK_RECEIVED;	/* To indicate nack received */
	else
		return I2C_TRANS_FAILURE;	/* data transmission failure */
}

u8 I2C_Read_Ack(void)		/* I2C read ack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);	/* Enable TWI, generation of ack */
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job */
	return TWDR;							/* Return received data */
}

u8 I2C_Read_Nack(void)		/* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	return TWDR;				/* Return received data */
}

void I2C_Stop(void)			/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);	/* Enable TWI, generate stop */
	while(TWCR&(1<<TWSTO));					/* Wait until stop condition execution */
}

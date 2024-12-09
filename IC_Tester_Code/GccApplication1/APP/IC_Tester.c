/*
 * IC_Tester.c
 *
 * Created: 12/1/2024 8:45:38 PM
 *  Author: Blu-Ray
 */ 

#include "IC_Tester.h"



static void init_ic_pins(const IC_74xx_t *ic);

static void init_ic_pins(const IC_74xx_t *ic)
{
	u8 counter;
	
	for (counter = 0; counter < IC_74xx_PINS; counter++)
	{
		DIO_InitPin(ic->pins[counter].channel, ic->pins[counter].status);
	}
}

static const c8 *err_message= "Unknown IC";

const IC_74xx_t IC_74xx_family[IC_74XX_NUM] =
{
	// IC: 7400
	{
        .ic_name = "7400", 
		.pins = {
			{SOCKET_PIN1, OUTPUT},		{SOCKET_PIN2, OUTPUT}, 
			{SOCKET_PIN3, INPUT_FREE},	{SOCKET_PIN4, OUTPUT}, 
			{SOCKET_PIN5, OUTPUT},		{SOCKET_PIN6, INPUT_FREE}, 
			{SOCKET_PIN7, OUTPUT},		{SOCKET_PIN8, INPUT_FREE}, 
			{SOCKET_PIN9, OUTPUT},		{SOCKET_PIN10, OUTPUT}, 
			{SOCKET_PIN11, INPUT_FREE}, {SOCKET_PIN12, OUTPUT}, 
			{SOCKET_PIN13, OUTPUT},		{SOCKET_PIN14, OUTPUT}
		}, 
		.truth_table = {
			{.pins_logic = {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1}},
			{.pins_logic = {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1}},
			{.pins_logic = {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}},
			{.pins_logic = {1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1}}
		}
    },
	// IC: 7402
	{
		.ic_name = "7402",
		.pins = {
			{SOCKET_PIN1,  INPUT_FREE}, {SOCKET_PIN2,  OUTPUT},
			{SOCKET_PIN3,  OUTPUT},		{SOCKET_PIN4,  INPUT_FREE},
			{SOCKET_PIN5,  OUTPUT},		{SOCKET_PIN6,  OUTPUT},
			{SOCKET_PIN7,  OUTPUT},		{SOCKET_PIN8,  OUTPUT},
			{SOCKET_PIN9,  OUTPUT},		{SOCKET_PIN10, INPUT_FREE},
			{SOCKET_PIN11, OUTPUT},		{SOCKET_PIN12, OUTPUT},
			{SOCKET_PIN13, INPUT_FREE}, {SOCKET_PIN14, OUTPUT}
		},
		.truth_table = {
			{.pins_logic = {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1}},
			{.pins_logic = {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1}},
			{.pins_logic = {0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1}},
			{.pins_logic = {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}}
		}
	},	
	// IC: 7404
	{
		.ic_name = "7404",
		.pins = {
			{SOCKET_PIN1,  INPUT_FREE}, {SOCKET_PIN2,  OUTPUT},
			{SOCKET_PIN3,  INPUT_FREE}, {SOCKET_PIN4,  OUTPUT},
			{SOCKET_PIN5,  INPUT_FREE}, {SOCKET_PIN6,  OUTPUT},
			{SOCKET_PIN7,  OUTPUT},		{SOCKET_PIN8,  OUTPUT},
			{SOCKET_PIN9,  INPUT_FREE}, {SOCKET_PIN10, OUTPUT},
			{SOCKET_PIN11, INPUT_FREE}, {SOCKET_PIN12, OUTPUT},
			{SOCKET_PIN13, INPUT_FREE}, {SOCKET_PIN14, OUTPUT}
		},
		.truth_table = {
			{.pins_logic = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}},
			{.pins_logic = {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1}},
			{.pins_logic = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}},
			{.pins_logic = {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1}}
		}
	},
	// IC: 7408
	{
		.ic_name = "7408",
		.pins = {
			{SOCKET_PIN1,  OUTPUT},		{SOCKET_PIN2,  OUTPUT},
			{SOCKET_PIN3,  INPUT_FREE}, {SOCKET_PIN4,  OUTPUT},
			{SOCKET_PIN5,  OUTPUT},		{SOCKET_PIN6,  INPUT_FREE},
			{SOCKET_PIN7,  OUTPUT},		{SOCKET_PIN8,  INPUT_FREE},
			{SOCKET_PIN9,  OUTPUT},		{SOCKET_PIN10, OUTPUT},
			{SOCKET_PIN11, INPUT_FREE}, {SOCKET_PIN12, OUTPUT},
			{SOCKET_PIN13, OUTPUT},		{SOCKET_PIN14, OUTPUT}
		},
		.truth_table = {
			{.pins_logic = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
			{.pins_logic = {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1}},
			{.pins_logic = {0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1}},
			{.pins_logic = {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1}}
		}
	},
	// IC: 7432
	{
		.ic_name = "7432",
		.pins = {
			{SOCKET_PIN1,  OUTPUT},		{SOCKET_PIN2,  OUTPUT},
			{SOCKET_PIN3,  INPUT_FREE}, {SOCKET_PIN4,  OUTPUT},
			{SOCKET_PIN5,  OUTPUT},		{SOCKET_PIN6,  INPUT_FREE},
			{SOCKET_PIN7,  OUTPUT},		{SOCKET_PIN8,  INPUT_FREE},
			{SOCKET_PIN9,  OUTPUT},		{SOCKET_PIN10, OUTPUT},
			{SOCKET_PIN11, INPUT_FREE}, {SOCKET_PIN12, OUTPUT},
			{SOCKET_PIN13, OUTPUT},		{SOCKET_PIN14, OUTPUT}
		},
		.truth_table = {
			{.pins_logic = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
			{.pins_logic = {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1}},
			{.pins_logic = {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}},
			{.pins_logic = {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1}}
		}
	},
	// IC: 7486
	{
		.ic_name = "7486",
		.pins = {
			{SOCKET_PIN1,  OUTPUT},		{SOCKET_PIN2,  OUTPUT},
			{SOCKET_PIN3,  INPUT_FREE}, {SOCKET_PIN4,  OUTPUT},
			{SOCKET_PIN5,  OUTPUT},		{SOCKET_PIN6,  INPUT_FREE},
			{SOCKET_PIN7,  OUTPUT},		{SOCKET_PIN8,  INPUT_FREE},
			{SOCKET_PIN9,  OUTPUT},		{SOCKET_PIN10, OUTPUT},
			{SOCKET_PIN11, INPUT_FREE}, {SOCKET_PIN12, OUTPUT},
			{SOCKET_PIN13, OUTPUT},		{SOCKET_PIN14, OUTPUT}
		},
		.truth_table = {
			{.pins_logic = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
			{.pins_logic = {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1}},
			{.pins_logic = {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}},
			{.pins_logic = {1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1}}
		}
	}
};

const c8 *test_ic_74xx(void)
{
	u8 ic_counter, cases_counter, pin_counter;
	DIO_PinVolt_type logic;
	u8 flag=1;
	
	for (ic_counter = 0; ic_counter < IC_74XX_NUM; ic_counter++)
	{
		flag=1;
		init_ic_pins(IC_74xx_family+ic_counter);
		
		for (cases_counter = 0; cases_counter < 4; cases_counter++)
		{
			for (pin_counter = 0; pin_counter < IC_74xx_PINS; pin_counter++)
			{
				if (IC_74xx_family[ic_counter].pins[pin_counter].status == OUTPUT)
				{
					DIO_WritePin(
						IC_74xx_family[ic_counter].pins[pin_counter].channel,
						READ_PIN(IC_74xx_family[ic_counter].truth_table[cases_counter].ic_logic, pin_counter)
					 );
				}
			}
			
			for (pin_counter = 0; pin_counter < IC_74xx_PINS; pin_counter++)
			{
				if (IC_74xx_family[ic_counter].pins[pin_counter].status == INPUT_FREE)
				{
					logic = DIO_ReadPin(IC_74xx_family[ic_counter].pins[pin_counter].channel);
					if (READ_PIN(IC_74xx_family[ic_counter].truth_table[cases_counter].ic_logic, pin_counter) != logic)
					{
						flag = 0;
						break;
					}
				}
			}
			if (flag == 0) 
			{
				break;
			}
		}
		if (flag)
		{
			return IC_74xx_family[ic_counter].ic_name;
		}
	}
	
	return err_message;
}
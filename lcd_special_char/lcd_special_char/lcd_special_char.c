/* Activity: lcd_special_char
 *
 * @Author     Shrikrishna Bhagirath Rajule
 * @Date       2020/03/20
 *
 * AIM:
 * To interface the LCD on Proteus 8 Demonstration and to perform the Activity 1
 * i) Sine Wave
 * ii)Special Characters
 *
 *
 * CONNECTIONS:
 * 
 * LCD:                 Port B and Port D       <br>
 * Control Pins:        <br>
 *	 RS		    :       PB0						<br>
 *	 RW			:       PB2						<br>
 *	 EN			:       PB1						<br>
 * Data Pins:           <br>
 *	 DB7		:	    PD7						<br>
 *	 DB6		:	    PD6						<br>
 *	 DB5		:	    PD5						<br>
 *	 DB4		:	    PD4						<br>
 *  
 * 
 * MACRO_DEFINITIONS:
 * 
 * Macros for LCD:			<br>
 *				                     
 * lcd_data_ddr_reg			:		DDRD			<br>
 * lcd_control_ddr_reg		:	    DDRB			<br>
 *
 * lcd_data_port_reg		:		PORTD			<br>
 * lcd_control_port_reg		:		PORTB			<br>
 *
 * RS_pin					:			0			<br>
 * RW_pin					:			2			<br>
 * EN_pin					:			1			<br>
 *
 * DB7_pin					:			7			<br>
 * DB6_pin					:			6			<br>
 * DB5_pin					:			5			<br>
 * DB4_pin					:			4			<br>
 * 
 */


//---------------------------------- HEADER FILES -----------------------------------------------------

#include "week4_simulation.h"				// Header file included that contains macro definitions essential for Proteus Demonstration
#include "lcd.h"							// LCD Header file included that contains function definitions essential to deal with LCD
#include <util/delay.h>						// Standard AVR Delay Library
#include <stdio.h>						    // Standard C Library for standard input output
#include <stdbool.h>						// Standard C Library for Boolean Type


//---------------------------------- GLOBAL VARIABLES ---------------------------------------------------
// Sine wave
unsigned char positive_1[8] = {0x00,0x07,0x08,0x10,0x00,0x00,0x00,0x00};
unsigned char positive_2[8] = {0x00,0x1C,0x02,0x01,0x00,0x00,0x00,0x00};
unsigned char negative_1[8] = {0x00,0x00,0x00,0x00,0x10,0x08,0x07,0x00};
unsigned char negative_2[8] = {0x00,0x00,0x00,0x00,0x01,0x02,0x1C,0x00};

// Arrow-->Apple
unsigned char apple_1[8] = {0x00,0x1E,0x1F,0x1F,0x1F,0x1F,0x0F,0x07};
unsigned char apple_2[8] = {0x00,0x0F,0x1F,0x1F,0x1F,0x1F,0x1E,0x1C};
unsigned char u_leaf[8] = {0x00,0x01,0x17,0x17,0x17,0x18,0x10,0x10};
unsigned char f_leaf[8] = {0x00,0x00,0x00,0x02,0x06,0x06,0x08,0x1F};
unsigned char arrow_head[8] = {0x00,0x08,0x0C,0x1E,0x1F,0x1E,0x0C,0x08};
unsigned char arrow_tail_1[8] = {0x00,0x00,0x00,0x1F,0x1F,0x1F,0x00,0x00};
unsigned char arrow_tail_2[8] = {0x00,0x00,0x0C,0x0F,0x0F,0x0F,0x0C,0x00};

// Fight against Covid-19
unsigned char hand_1[8] = {0x00,0x14,0x14,0x1F,0x1F,0x1E,0x00,0x00};
unsigned char hand_2[8] = {0x00,0x08,0x08,0x1F,0x1F,0x1E,0x00,0x00};
unsigned char hand_3[8] = {0x00,0x0A,0x0A,0x1F,0x1F,0x1E,0x00,0x00};
unsigned char water_drop[8] = {0x00,0x04,0x0E,0x1F,0x1F,0x1F,0x1F,0x0E};
unsigned char namaste[8] = {0x00,0x04,0x0E,0x0E,0x0E,0x1F,0x1B,0x1B};
unsigned char home[8] = {0x00,0x0C,0x0C,0x1F,0x1D,0x1F,0x13,0x13};
unsigned char corona[8] = {0x00,0x11,0x0E,0x0E,0x0E,0x11,0x00,0x00};
	
	
//---------------------------------- FUNCTIONS ---------------------------------------------------------


//----------------------------- LCD FUNCTIONS ----------------------------------------------------------


/* 
 * Function Name: sine_wave
 * Input: None
 * Output: None
 * Logic: Function to perform Activity 1 : Sine Wave
 * Example Call: sine_wave();
 */
void sine_wave (void)
{

// To display scrolling text, "Sine wave" for 5 seconds

	char text[] = "Sine wave";
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_string(1,16,text);			// Position and Text Display
	
	int i=0;
	while(i<32)
	{
		lcd_wr_command(0x18);		//Scrolling Display
		i++;
		_delay_ms(150);				// Delay of 150 milliseconds
	}
	

// To display the Output of Sine wave for 5 seconds	
	
	lcd_clear();					// Clears LCD
	lcd_home();						// Sets the cursor's to home i.e. 1st row, 1st column
	
	lcd_create_custom_character(1,positive_1);      // Creates the first half of the Positive Sine Wave
	lcd_create_custom_character(2,positive_2);      // Creates the second half of the Positive Sine Wave
	lcd_create_custom_character(3,negative_1);      // Creates the first half of the Negative Sine Wave
	lcd_create_custom_character(4,negative_2);      // Creates the second half of the Negative Sine Wave
	
// Displays the Custom Character at particular positions to form a SINE WAVE on both the lines of the LCD 
	lcd_wr_char(1,1,1);
	_delay_ms(40);                       // Delay of 40 milliseconds          
	lcd_wr_char(1,2,2);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,3,3);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,4,4);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,5,1);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,6,2);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,7,3);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,8,4);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,9,1);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,10,2);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,11,3);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,12,4);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,13,1);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,14,2);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,15,3);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(1,16,4);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,1,1);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,2,2);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,3,3);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,4,4);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,5,1);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,6,2);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,7,3);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,8,4);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,9,1);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,10,2);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,11,3);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,12,4);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,13,1);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,14,2);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,15,3);
	_delay_ms(40);                       // Delay of 40 milliseconds 
	lcd_wr_char(2,16,4);
	_delay_ms(2000);                     // Delay of 2 seconds 
}


/* 
 * Function Name: special_char
 * Input: None
 * Output: None
 * Logic: Function to perform Activity 1 : Special Character
 * Example Call: special_char();
 */
void special_char (void)
{
// To display scrolling text, "Special Characters" for 5 seconds

	char text1[] = "Special Characters";
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_string(1,16,text1);			// Position and Text Display
	
	int i=0;
	while(i<34)
	{
		lcd_wr_command(0x18);		//Scrolling Display
		i++;
		_delay_ms(130);				// Delay of 130 milliseconds
	}
	
// To display the Output of Special Characters in the sequence "! @ # $ % & *"	
	
	lcd_clear();					// Clears LCD
	lcd_home();						// Sets the cursor's to home i.e. 1st row, 1st column
	
	char text2[] = "! @ # $ % & *";
	lcd_string(1,2,text2);          // To display the text/string at particular position on the LCD
	_delay_ms(5000);				// Delay of 5 seconds
}


/* 
 * Function Name: additional_part
 * Input: None
 * Output: None
 * Logic: Function to perform Activity 1 : Creative Part
 * Example Call: additional_part();
 */
void additional_part(void)
{
	
	char text3[] = "Additional  part";
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_string(1,1,text3);			// Position and Text Display
	_delay_ms(3000);				// Delay of 3 seconds
	
	lcd_clear();					// Clears LCD
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_home();						// Sets the cursor's to home i.e. 1st row, 1st column
	
// Arrow and Apple

	char text4[] = "ARROW-->APPLE";
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_string(1,22,text4);			// Position and Text Display
	
	int i=0;
	while(i<34)
	{
		lcd_wr_command(0x1C);		//Scrolling Display
		i++;
		_delay_ms(200);				// Delay of 200 milliseconds
	}
	
	lcd_clear();					// Clears LCD
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_home();						// Sets the cursor's to home i.e. 1st row, 1st column
	
	lcd_create_custom_character(1,apple_1);           // Creates the first half of the Apple
	lcd_create_custom_character(2,apple_2);           // Creates the second half of the Apple
	lcd_create_custom_character(3,u_leaf);            // Creates the upright leaf
	lcd_create_custom_character(4,f_leaf);            // Creates the fallen leaf
	lcd_create_custom_character(5,arrow_head);        // Creates the Arrow head
	lcd_create_custom_character(6,arrow_tail_1);      // Creates the Arrow tail 1
	lcd_create_custom_character(7,arrow_tail_2);      // Creates the Arrow tail 2
	
	lcd_wr_char(2,8,1);
	lcd_wr_char(2,9,2);
	lcd_wr_char(1,9,3);
	lcd_wr_char(2,3,4);
	lcd_wr_char(2,2,5);
	lcd_wr_char(2,1,6);
	
	for(int j=3;j<22;j++)
	{
		lcd_clear();					// Clears LCD
		lcd_wr_char(2,8,1);
		lcd_wr_char(2,9,2);
		lcd_wr_char(1,9,3);
		lcd_wr_char(2,j,5);
		lcd_wr_char(2,j-1,6);
		lcd_wr_char(2,j-2,7);
		_delay_ms(100);                 // Delay of 100 milliseconds
	}
	lcd_clear();					// Clears LCD
	lcd_wr_char(2,7,1);
	lcd_wr_char(2,10,2);
	lcd_wr_char(2,11,4);
	_delay_ms(2000);				// Delay of 2 seconds
	
// Fight against Covid-19

	lcd_clear();					// Clears LCD
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_home();						// Sets the cursor's to home i.e. 1st row, 1st column
	
	char text5[] = "Fight XX Covid-19";
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_string(1,22,text5);			// Position and Text Display
	
	int k=0;
	while(k<34)
	{
		lcd_wr_command(0x1C);		//Scrolling Display
		k++;
		_delay_ms(200);				// Delay of 200 milliseconds
	}
	
	lcd_clear();					// Clears LCD
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_home();						// Sets the cursor's to home i.e. 1st row, 1st column
	
	lcd_create_custom_character(1,hand_1);              // Creates hand position 1
	lcd_create_custom_character(2,hand_2);              // Creates hand position 2
	lcd_create_custom_character(3,hand_3);              // Creates hand position 3
	lcd_create_custom_character(4,water_drop);          // Creates water drop to wash hands
	lcd_create_custom_character(5,namaste);             // Creates namaste for greeting
	lcd_create_custom_character(6,home);                // Creates home to stay safe
	lcd_create_custom_character(7,corona);              // Creates Corona Virus

	char text6[] = "Namaste";
	char text7[] = "Stay Home";
	char text8[] = "Wash Hands";
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_string(1,22,text6);			// Position and Text Display
	lcd_wr_char(1,29,5);            // Namaste Symbol
	
	int q=0;
	while(q<34)
	{
		lcd_wr_command(0x18);		//Scrolling Display
		q++;
		_delay_ms(100);				// Delay of 100 milliseconds
	}
	
	lcd_clear();					// Clears LCD
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_string(2,22,text7);			// Position and Text Display
	lcd_wr_char(2,31,6);            // Stay Home Symbol
	
	int o=0;
	while(o<34)
	{
		lcd_wr_command(0x1C);		//Scrolling Display
		o++;
		_delay_ms(100);				// Delay of 100 milliseconds
	}
	
	lcd_clear();					// Clears LCD
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_string(1,22,text8);			// Position and Text Display
	lcd_wr_char(1,32,1);            // Hand Wash Symbol
	
	int p=0;
	while(p<34)
	{
		lcd_wr_command(0x18);		//Scrolling Display
		p++;
		_delay_ms(100);				// Delay of 100 milliseconds
	}
	
	lcd_clear();					// Clears LCD
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_home();						// Sets the cursor's to home i.e. 1st row, 1st column
	
	int n=4;
	while(n<18)
	{
		lcd_clear();                         // Clears LCD
		lcd_wr_char(1,1,5);
		lcd_wr_char(2,1,5);
		lcd_wr_char(1,2,6);
		lcd_wr_char(2,2,6);					
		for(int l=1;l<4;l++)
		{
			lcd_wr_char(1,3,4);
			lcd_wr_char(2,3,l);
			_delay_ms(100);                  // Delay of 100 milliseconds
		}
		lcd_wr_char(1,n,7);
		lcd_wr_char(2,n,7);
		n++;
		_delay_ms(200);                     // Delay of 200 milliseconds
	}
	char text9[] = "WE";
	char text10[] = "WIN";
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_string(1,13,text9);			// Position and Text Display
	lcd_string(2,13,text10);			// Position and Text Display
	_delay_ms(2000);                // Delay of 2 seconds
	
	lcd_clear();                         // Clears LCD
	
	char text11[] = "Thank You";
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_string(1,4,text11);			// Position and Text Display
	_delay_ms(2000);                // Delay of 2 seconds
}




//---------------------------------- MAIN ----------------------------------------------------------------
/*
 *
 * @brief      Main Function
 *
 * @details    First Initializes LCD and calls functions to perform Activity 1
 *
 * @return 0 
 */
int main(void) 
{
	
	lcd_port_config();					// Initialize the LCD port
	lcd_init();							// Initialize the LCD
	
	
	lcd_clear();					// Clears LCD
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_home();						// Sets the cursor's to home i.e. 1st row, 1st column
		
	sine_wave();					// Calls function "sine_wave" to display Sine Wave
		
	lcd_clear();					// Clears LCD
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_home();						// Sets the cursor's to home i.e. 1st row, 1st column
		
	special_char();					// Calls function "special_char" to display Special Characters
	
	lcd_clear();					// Clears LCD
	lcd_wr_command(0x0C);           // Display ON and Cursor OFF
	lcd_home();						// Sets the cursor's to home i.e. 1st row, 1st column
	
	additional_part();              // Calls function "additional_part" to display creative part
	
	return 0;
}


//---------------------------------- END ------------------------------------------------------------------
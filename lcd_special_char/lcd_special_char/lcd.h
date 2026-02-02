/*  lcd.h
 * 
 * @Author     Shrikrishna Bhagirath Rajule
 * @Date       2020/03/20
 */ 

#ifndef LCD_H_
#define LCD_H_

// This function configures LCD pins as output
void lcd_port_config(void);

// This function configures the LCD to work in 4 bit mode instead of 8 bit mode
// to reduce the number of data lines required to be used
void lcd_set_4bit (void);

// This function gives specific command values to the LCD to perform necessary functions
// This also points address for storing newly created custom character in CGRAM
void lcd_wr_command (unsigned char cmd);

// This function initializes the LCD
void lcd_init(void);

// This function sets the cursor's to home i.e. 1st row, 1st column
void lcd_home(void);

// This function sets the cursor to the specified position
void lcd_cursor(char row, char column);

// This function clears LCD by giving specific command as input to lcd_wr_command() function
void lcd_clear(void);

// This function prints an alpha-numeric character at specified (row, column) position on LCD
void lcd_wr_char(char row, char column, unsigned char alpha_num_char);

// This function prints the given string on the LCD at the specified (row, column) position
void lcd_string(char row, char column, char* str);

// This function prints any integer value or value in a variable as integer
// on the specified location and up to the specified number of digits on LCD
void lcd_numeric_value(char row, char coloumn, int val, int digits);

// This function writes custom character data or 5*8 pixel values in DDRAM 
void lcd_wr_custom_char(unsigned char hexa);

// This function creates the Custom Character
void lcd_create_custom_character(unsigned char location,unsigned char *pattern);

#endif /* LCD_H_ */
/* Experiment: line_follow_path_plan
 *
 * @author     Shrikrishna Bhagirath Rajule
 * @date       2020/03/20
 *
 * AIM:		   
 * To make the robot, follow any particular path on the given arena.
 *
 *
 * CONNECTIONS:
 * 
 * 3 White-Line sensors:          Port B and Port C                       <br>
 * 
 *   left_wl_sensor_pin				:		     PB3	( MOSI / IO11 )         <br>
 *   center_wl_sensor_pin			:		     PB4	( MISO / IO12 )         <br>
 *   right_wl_sensor_pin			:			 PC0	( AD0 / ADC0 )          <br>
 *
 * Motors:                Port D           <br>
 *
 *   motors_RB_pin			:		PD7	        <br>
 *   motors_RF_pin			:		PD6	        <br>
 *   motors_LF_pin			:		PD2		    <br>	
 *   motors_LB_pin			:		PD4		    <br>	
 *   motors_pwm_R_pin       :       PD5         <br>
 *   motors_pwm_L_pin		:		PD3			<br>
 *
 *
 * MACRO_DEFINITIONS:
 *
 * Macros for 3 White-Line sensors:                   <br>
 *
 * wl_l_c_sensors_ddr_reg		   :     	DDRB              <br>
 * wl_l_c_sensors_port_reg		   :    	PORTB             <br>
 * wl_l_c_sensors_pin_reg		   :     	PINB              <br>
 * left_wl_sensor_pin			   :      	PB3               <br>
 * center_wl_sensor_pin			   :        PB4               <br>
 * 
 * wl_r_sensors_ddr_reg			   :        DDRC              <br>
 * wl_r_sensors_port_reg		   :      	PORTC             <br>
 * wl_r_sensors_pin_reg			   :        PINC              <br>
 * right_wl_sensor_pin			   :      	PC0               <br>
 *
 * Macros for Motors:                                    <br>
 * 
 * motors_dir_ddr_reg			    :    	 DDRD                    <br>
 * motors_dir_port_reg				:        PORTD                   <br> 
 * motors_RB_pin				    :        PD7                     <br>
 * motors_RF_pin				    :     	 PD6                     <br>
 * motors_LF_pin			        :        PD2                     <br>
 * motors_LB_pin				    :        PD4	                 <br>
 *
 * motors_pwm_ddr_reg				:        DDRD                    <br>
 * motors_pwm_port_reg				:        PORTD                   <br>
 * motors_pwm_R_pin				    :        PD5		             <br>
 * motors_pwm_L_pin				    :        PD3			         <br>
 *
 */ 


//---------------------------------- HEADER FILES -----------------------------------------------------

#include "week4_simulation.h"				// Header file included that contains macro definitions essential for Proteus Demonstration
#include <util/delay.h>						// Standard AVR Delay Library
#include <stdio.h>						    // Standard C Library for standard input output
#include <stdbool.h>						// Standard C Library for Boolean Type
#include <stdlib.h>                         // Standard C Library


//---------------------------------- GLOBAL VARIABLES ---------------------------------------------------

unsigned char left_sensor   = 0;				///< Left line sensor pin value
unsigned char center_sensor = 0;				///< Center line sensor pin value
unsigned char right_sensor	= 0;				///< Right line sensor pin value

bool left_status   = false;						///< False (F) if Left sensor is on white surface, True (T) if on black line
bool center_status = false;						///< False (F) if Center sensor is on white surface, True (T) if on black line
bool right_status  = false;						///< False (F) if Right sensor is on white surface, True (T) if on black line

float path[] = {4.0, 5.0, 7.0, 8.0, 6.0};					///< Path input array for robot traversal (Path_1)
//float path[] = {2.0, 3.0, 6.0, 2.0, 4.0};			        ///< Path input array for robot traversal (Path_2)
float path_col[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};          ///< Path array, to be used instead of 'path' array, for adding one last element to the array to reach the GOAL

float current_pos = 4.5;                    ///< Current Position of the turtle in terms of column
int row = 0;                                ///< Current Position of the turtle in terms of row

int i = 0;                                  ///< i is used as a index to access the next position from the 'path_col[]' array
int j = 1;                                  ///< j is used to make left or right turns, in the row 3 of the arena

bool flag = true;                           ///< 'flag' --> true, means to continue with the while loop till the robot reaches the destination

bool dir_status = true;                     ///< Tells the "configure_path" function which side to turn, after updating the 'dir_status' from the "configure_direction" function; ...
											/// if 'dir_status' is true(left), then the turtle should turn in the right direction in the "configure_path" funciton; ...
											/// and vice-versa if 'dir_status' is false 

bool dir = true;                            ///< When 'dir' is true, then the turtle should configure the direction when it reaches the next check point; ...
											/// here check point is when all the white line sensors are on black line
bool pat = false;                          ///< When 'path' is true, then the turtle should configure the direction when it reaches the next check point; ...
											/// here check point is when all the white line sensors are on black line

bool last = false;                          ///< 'last' is a variable, used to tell the robot to follow a different set of track configuration; ...
											/// When the turtle reaches the penultimate row, to follow the white line instead of black


//---------------------------------- FUNCTIONS ---------------------------------------------------------

//-----------------------------CONFIGURATION FUNCTIONS -------------------------------------------------


/* 
 * Function Name: wl_sensors_port_config
 * Input: None
 * Output: None
 * Logic: This function configures the 3 White Line Sensor Pins as Input and Activates Pull-Up for these sensor pins
 * Example Call: wl_sensors_port_config();
 */
void wl_sensors_port_config()
{
	
	// Makes 3 White Line Sensor Pins as Input
	wl_l_c_sensors_ddr_reg	&= ~((1<<left_wl_sensor_pin) | (1<<center_wl_sensor_pin)) ;
	wl_r_sensors_ddr_reg	&= ~(1<<right_wl_sensor_pin) ;
	
	// Activates Pull-Up for these sensor pins
	wl_l_c_sensors_port_reg	|= ((1<<left_wl_sensor_pin) | (1<<center_wl_sensor_pin)) ;
	wl_r_sensors_port_reg	|= (1<<right_wl_sensor_pin) ;
}


/* 
 * Function Name: motors_pin_config
 * Input: None
 * Output: None
 * Logic: Function to configure pins of ATmega2560 to which pins of L293D Motor Driver IC is connected
 * Example Call: motors_pin_config();
 */
void motors_pin_config(void) 
{
	//To set  motor pins as output
	motors_dir_ddr_reg |= ((1<<motors_RB_pin) | (1<<motors_RF_pin) | (1<<motors_LF_pin) | (1<<motors_LB_pin)) ;	
			
	//To initially set them to LOW to stop motors
	motors_dir_port_reg &= ~((1<<motors_RB_pin) | (1<<motors_RF_pin) | (1<<motors_LF_pin) | (1<<motors_LB_pin)) ;	    
}


/* 
 * Function Name: pwm_pin_config
 * Input: None
 * Output: None
 * Logic: Function to configure left and right channel pins of the L293D Motor Driver IC for PWM
 * Example Call: pwm_pin_config();
 */
void pwm_pin_config(void)
{

	//To set left and right channel pin as output
	motors_pwm_ddr_reg |= ((1<<motors_pwm_R_pin) | (1<<motors_pwm_L_pin)) ;
		
	//To initially set them to HIGH to enable motors
	motors_pwm_port_reg |= ((1<<motors_pwm_R_pin) | (1<<motors_pwm_L_pin)) ;		
}


/* 
 * Function Name: timer_pwm_init
 * Input: None
 * Output: None
 * Logic: Function to initialize Timer 0 and 2 in 8-bit Fast PWM mode for speed control of motors
 * Example Call: timer_pwm_init();
 */
void timer_pwm_init(void)
{
	
	// To configure Compare Output Mode bits to select Clear on Compare setting in TCCRnA register
	// To configure Waveform Generation Mode bits for 8-bit Fast PWM in TCCRnA and TCCRnB register
	// For Timer 0
	TCCR0A_reg |= ((1<<WGM0_bit) | (1<<COMB1_bit));
	TCCR0A_reg &= ~((1<<WGM1_bit) | (1<<COMB0_bit));

	// For Timer 2
	TCCR2A_reg |= ((1<<WGM0_bit) | (1<<COMB1_bit));
	TCCR2A_reg &= ~((1<<WGM1_bit) | (1<<COMB0_bit));
	
	// To configure Clock Select bits to choose prescalar division factor of 64
	// For Timer 0
	TCCR0B_reg |= ((1<<CS0_bit) | (1<<CS1_bit));
	TCCR0B_reg &= ~((1<<CS2_bit) | (1<<WGM2_bit));
	
	// For Timer 2
	TCCR2B_reg |= ((1<<CS2_bit));
	TCCR2B_reg &= ~((1<<CS1_bit) | (1<<CS0_bit) | (1<<WGM2_bit));
	
	// To make values in both Output Compare Registers as 0
	OCR0B_reg = 0x00;
	OCR2B_reg = 0x00;
}


/* 
 * Function Name: set_duty_cycle
 * Input: left_motor_pwm  :  Left motor speed 0 to 255
		  right_motor_pwm :  Right motor speed 0 to 255
 * Output: None
 * Logic: Function to control the speed of both the motors of robot
 * Example Call: set_duty_cycle();
 */
void set_duty_cycle(unsigned char left_motor_pwm, unsigned char right_motor_pwm)
{
	OCR2B_reg = left_motor_pwm;
	OCR0B_reg = right_motor_pwm;
}


//-----------------------------MOTOR and PATH LOGIC Related FUNCTIONS -------------------------------------------------


/* 
 * Function Name: right
 * Input:  None
 * Output: None
 * Logic:  Function to make the robot move "right"
 * Example Call: right();
 */
void right(void) 
{
	
	//To set RB and LF and reset RF and LB
	motors_dir_port_reg |= ((1<<motors_RB_pin) | (1<<motors_LF_pin)) ;	
	motors_dir_port_reg &= ~((1<<motors_RF_pin) | (1<<motors_LB_pin)) ;
}


/* 
 * Function Name: left
 * Input:  None
 * Output: None
 * Logic:  Function to make the robot move "left"
 * Example Call: left();
 */
void left(void) 
{

	//To set RF and LB and reset RB and LF
	motors_dir_port_reg |= ((1<<motors_RF_pin) | (1<<motors_LB_pin)) ;	
	motors_dir_port_reg &= ~((1<<motors_RB_pin) | (1<<motors_LF_pin)) ;
}


/* 
 * Function Name: stop
 * Input:  None
 * Output: None
 * Logic:   Function to make the robot "stop"
 * Example Call: stop();
 */
void stop(void) 
{
	
	//To reset RF, LB, RB and LF	
	motors_dir_port_reg &= ~((1<<motors_RB_pin) | (1<<motors_LF_pin) | (1<<motors_RF_pin) | (1<<motors_LB_pin)) ;
}


/* 
 * Function Name: forward
 * Input:  None
 * Output: None
 * Logic:  Function to make the robot move "forward"
 * Example Call: forward();
 */
void forward()
{
	
	//To set RF and LF and reset RB and LB
	motors_dir_port_reg |= ((1<<motors_RF_pin) | (1<<motors_LF_pin)) ;
	motors_dir_port_reg &= ~((1<<motors_RB_pin) | (1<<motors_LB_pin)) ;
}


/* 
 * Function Name: read_wl_sensors
 * Input: None
 * Output: None
 * Logic: This function reads the sensors pins and updates to the boolean type; black line --> true and white surface --> false
 * Example Call: read_wl_sensors();
 */
void read_wl_sensors()
{
	
	// To update the left_sensor, center_sensor and right_sensor variables
	// by reading the corresponding sensor pin from PIN register
	left_sensor = wl_l_c_sensors_pin_reg;
	center_sensor = wl_l_c_sensors_pin_reg;
	right_sensor = wl_r_sensors_pin_reg;
	
	// To update the boolean type left_status, center_status and right_status variables based on
	// the data of left_sensor, center_sensor and right_sensor variables to either true (T) or false (F)
	// true (T) = if the sensor is on black line
	// false (F) = if the sensor is on white surface
	if((left_sensor & (1 << left_wl_sensor_pin)) == 0x08)
		left_status = true;
	else
		left_status = false;
	
	if((center_sensor & (1 << center_wl_sensor_pin)) == 0x10)
		center_status = true;
	else
		center_status = false;
	
	if((right_sensor & (1 << right_wl_sensor_pin)) == 0x01)
		right_status = true;
	else
		right_status = false;
}


/* 
 * Function Name: check_point
 * Input: None
 * Output: None
 * Return: true --> when there is a check point
		   false --> when there is no check point
 * Logic: This function looks for check points, when all the sensors are true or on black surface, is counted as a check point
 * Example Call: check_point();
 */
bool check_point()
{
	if((left_status == true) && (center_status == true) && (right_status == true))
	{
		if((i == 6) && (row == 6))
		{
			stop();
			flag = false;
			return false;
		}
		return true;
	}
	else
		return false;
}


/* 
 * Function Name: on_track
 * Input:  None
 * Output: None
 * Logic:  Function to keep the robot on track
 * Example Call: on_track();
 */
void on_track() 
{
		while(!((left_status == false) && (center_status == true) && (right_status == false)))
		{
			if(row == 1)
			{
				read_wl_sensors();
				if((left_status == true) && (center_status == false) && (right_status == false))
				{
					left();
					_delay_ms(1.3);
					forward();
					_delay_ms(0.2);
					stop();
				}
				else if((left_status == true) && (center_status == true) && (right_status == false))
				{
					left();
					_delay_ms(0.3);
					forward();
					_delay_ms(0.3);
					stop();
				}
				else if((left_status == false) && (center_status == false) && (right_status == true))
				{
					right();
					_delay_ms(1.2);
					forward();
					_delay_ms(0.3);
					stop();
				}
				else if((left_status == false) && (center_status == true) && (right_status == true))
				{
					right();
					_delay_ms(0.3);
					forward();
					_delay_ms(0.3);
					stop();
				}
				else if((left_status == false) && (center_status == false) && (right_status == false))
				{
					right();
					_delay_ms(0.1);
					forward();
					_delay_ms(0.2);
					left();
					_delay_ms(0.1);
					break;
				}
				else if((left_status == true) && (center_status == true) && (right_status == true))
				{
					forward();
					_delay_ms(380);
					break;
				}
			}
			else if(row == 3)
			{
				read_wl_sensors();
				if((left_status == true) && (center_status == false) && (right_status == false))
				{
					left();
					_delay_ms(10);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == true) && (center_status == true) && (right_status == false))
				{
					left();
					_delay_ms(5);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == false) && (center_status == false) && (right_status == true))
				{
					right();
					_delay_ms(10);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == false) && (center_status == true) && (right_status == true))
				{
					right();
					_delay_ms(5);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == false) && (center_status == false) && (right_status == false))
				{
					stop();
					_delay_ms(1000);
					while(j < 5)
					{
						if(j%2 != 0)
						{
							left();
							_delay_ms(2000);
							forward();
							_delay_ms(840);              // ## Path_2 values --> _delay_ms(780); 
							right();
							_delay_ms(2000);
							forward();
							_delay_ms(800);
							++j;
							break;
						}
						else
						{
							right();
							_delay_ms(2000);
							forward();
							_delay_ms(840);              // ## Path_2 values --> _delay_ms(700); 
							left();
							_delay_ms(2000);
							forward();
							_delay_ms(800);
							++j;
							break;
						}
					}
				}
				else if((left_status == true) && (center_status == true) && (right_status == true))
				{
					forward();
					_delay_ms(500);
					break;
				}
			}
			else if(row == 5)
			{
				read_wl_sensors();
				if(last)
				{
					if((left_status == false) && (center_status == true) && (right_status == true))
					{
						left();
						_delay_ms(10);
						forward();
						_delay_ms(10);
						stop();
					}
					else if((left_status == false) && (center_status == false) && (right_status == true))
					{
						left();
						_delay_ms(5);
						forward();
						_delay_ms(10);
						stop();
					}
					else if((left_status == true) && (center_status == true) && (right_status == false))
					{
						right();
						_delay_ms(10);
						forward();
						_delay_ms(10);
						stop();
					}
					else if((left_status == true) && (center_status == false) && (right_status == false))
					{
						right();
						_delay_ms(5);
						forward();
						_delay_ms(10);
						stop();
					}
					else if((left_status == false) && (center_status == true) && (right_status == false))
						last = false;
					
					forward();
					_delay_ms(10);
				}
				else 
				{
					if((left_status == true) && (center_status == false) && (right_status == false))
					{
						left();
						_delay_ms(10);
						forward();
						_delay_ms(10);
						stop();
					}
					else if((left_status == true) && (center_status == true) && (right_status == false))
					{
						left();
						_delay_ms(5);
						forward();
						_delay_ms(10);
						stop();
					}
					else if((left_status == false) && (center_status == false) && (right_status == true))
					{
						right();
						_delay_ms(10);
						forward();
						_delay_ms(10);
						stop();
					}
					else if((left_status == false) && (center_status == true) && (right_status == true))
					{
						right();
						_delay_ms(5);
						forward();
						_delay_ms(10);
						stop();
					}
					else if((left_status == true) && (center_status == false) && (right_status == true))
						last = true;
					else if((left_status == true) && (center_status == true) && (right_status == true))
					{
						forward();
						_delay_ms(380);
						break;
					}	
				}
			}
			else if(row == 6)
			{
				read_wl_sensors();
				if((left_status == true) && (center_status == false) && (right_status == false))
				{
					left();
					_delay_ms(10);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == true) && (center_status == true) && (right_status == false))
				{
					left();
					_delay_ms(5);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == false) && (center_status == false) && (right_status == true))
				{
					right();
					_delay_ms(10);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == false) && (center_status == true) && (right_status == true))
				{
					right();
					_delay_ms(5);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == false) && (center_status == false) && (right_status == false))
				{
					right();
					_delay_ms(10);
					forward();
					_delay_ms(5);
					left();
					_delay_ms(10);
					break;
				}
				else if((left_status == true) && (center_status == true) && (right_status == true))
				{
					forward();
					_delay_ms(420);
					break;
				}
			}
			else
			{
				read_wl_sensors();
				if((left_status == true) && (center_status == false) && (right_status == false))
				{
					left();
					_delay_ms(10);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == true) && (center_status == true) && (right_status == false))
				{
					left();
					_delay_ms(5);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == false) && (center_status == false) && (right_status == true))
				{
					right();
					_delay_ms(10);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == false) && (center_status == true) && (right_status == true))
				{
					right();
					_delay_ms(5);
					forward();
					_delay_ms(10);
					stop();
				}
				else if((left_status == false) && (center_status == false) && (right_status == false))
				{
					right();
					_delay_ms(10);
					forward();
					_delay_ms(5);
					left();
					_delay_ms(10);
					break;
				}
				else if((left_status == true) && (center_status == true) && (right_status == true))
				{
					forward();
					_delay_ms(350);
					break;
				}
			}	
		}
		
		forward();
}


/* 
 * Function Name: configure_direction
 * Input: None
 * Output: None
 * Logic: This function configures the direction of the turtle, after looking at the next path from 'path_col' array
 * Example Call: configure_direction();
 */
void configure_direction()
{	
	if(row == 1)
	{
		if(path_col[i] > current_pos)
		{
			right();
			_delay_ms(2100);                                      // ## Path_2 values --> _delay_ms(1900);
			stop();
			dir_status = false;
			dir = false;
			pat = true;
			++row;
			forward();
			_delay_ms(1000);
			stop();
		}
		else
		{
			left();
			_delay_ms(2100);                                      // ## Path_2 values --> _delay_ms(1900);
			stop();
			dir_status = true;
			dir = false;
			pat =true;
			++row;
			forward();
			_delay_ms(1000);
			stop();
		}	
	}
	else if(row == 3)
	{
		if(path_col[i] > current_pos)
		{
			right();
			_delay_ms(2200);
			stop();
			dir_status = false;
			dir = false;
			pat = true;
			++row;
			forward();
			_delay_ms(1000);
			stop();
		}
		else
		{
			left();
			_delay_ms(2200);
			stop();
			dir_status = true;
			dir = false;
			pat =true;
			++row;
			forward();
			_delay_ms(1000);
			stop();
		}
	}
	else if(row == 4)
	{
		if(path_col[i] > current_pos)
		{
			right();
			_delay_ms(2300);
			stop();
			dir_status = false;
			dir = false;
			pat = true;
			++row;
			forward();
			_delay_ms(1000);
			stop();
		}
		else
		{
			left();
			_delay_ms(2300);
			stop();
			dir_status = true;
			dir = false;
			pat =true;
			++row;
			forward();
			_delay_ms(1000);
			stop();
		}
	}
	else if(row == 5)
	{
		if(current_pos > path_col[i])
		{
			left();
			_delay_ms(2150);
			stop();
			dir_status = true;
			dir = false;
			pat = true;
			++row;
			forward();
			_delay_ms(1000);
			stop();
		}
		else
		{
			right();
			_delay_ms(2150);
			stop();
			dir_status = false;
			dir = false;
			pat = true;
			++row;
			forward();
			_delay_ms(1000);
			stop();
		}
	}
	else
	{
		if(path_col[i] > current_pos)
		{
			right();
			_delay_ms(2150);
			stop();
			dir_status = false;
			dir = false;
			pat = true;
			++row;
			forward();
			_delay_ms(1000);
			stop();
		}
		else
		{
			left();
			_delay_ms(2150);
			stop();
			dir_status = true;
			dir = false;
			pat =true;
			++row;
			forward();
			_delay_ms(1000);
			stop();
		}
	}
}


/* 
 * Function Name: configure_path
 * Input: None
 * Output: None
 * Logic: This function configures the path to be taken by the turtle, after comparing the current position with the 'path_col' array
 * Example Call: configure_path();
 */
void configure_path()
{
	if((row == 1) && (i == 0) && (current_pos == 4.5))
	{
		if(current_pos > path_col[i])
			current_pos = floor(current_pos);
		else
			current_pos = ceil(current_pos);
		
		if(current_pos == path_col[i])
		{
			if(dir_status)
			{
				right();
				_delay_ms(2200);
				stop();
				forward();
				_delay_ms(1000);
				++i;
				pat = false;
				dir = true;
			}
			else
			{
				left();
				_delay_ms(2200);
				stop();
				forward();
				_delay_ms(1000);
				++i;
				pat = false;
				dir = true;
			}
		}
		else
		{
			forward();
			_delay_ms(1000);
		}
	}
	else
	{
		if(current_pos > path_col[i])
			--current_pos;
		else if(current_pos < path_col[i])
			++current_pos;
		
		if(current_pos == path_col[i])
		{
			if(dir_status)
			{
				right();
				_delay_ms(2200);
				stop();
				forward();
				_delay_ms(1000);
				++i;
				pat = false;
				dir = true;
			}
			else
			{
				left();
				_delay_ms(2200);
				stop();
				forward();
				_delay_ms(1000);
				++i;
				pat = false;
				dir = true;
			}
		}
		else
		{
			forward();
			_delay_ms(1000);
		}
	}
}


//---------------------------------- MAIN ----------------------------------------------------------------

/*
 *
 * @brief      Main Function
 *
 * @details    First Initializes the 3 White Line Sensors , ADC , Motors and PWM pins. Then executes the logic for the line follower robot
 *
 * @returns 0
 */
int main() 
{
	
	wl_sensors_port_config();			// Initialize the three white line sensors
	motors_pin_config();		        // Initialize motor pins
	pwm_pin_config();			        // Initialize PWM pins as output
	timer_pwm_init();				    // Initialize Timer 0 and 2 for PWM
	
	set_duty_cycle(50,50);              // Sets the speed of the turtle
	
	for(int k=0; k<5; k++)              // Copying the values of the 'path' array to the new array 'path_col'
		path_col[k] = path[k];
	
	if(path_col[3] > 4.5)               // Adds a last element to the 'path_col' array to make the robot take the correct direction and path to reach the GOAL
		path_col[5] = 4.0;
	else
		path_col[5] = 5.0;
	
	while(flag)
	{
		read_wl_sensors();                    // Reads the White Line Sensors values every time the While loop executes
		on_track();                           // To keep the turtle on track and not deviate from black line
		_delay_ms(50);
		stop();                               // Stops the turtle
		
		if(check_point() && dir)              // Checks for the check point and also to see if it's the time for the turtle to take a turn in required direction or not 
			configure_direction();
		else if(check_point() && pat)        // Checks for the check point and also to see if it's the time for the turtle to configure path or not 
			configure_path();
	}
	
	return 0;
}
//---------------------------------- END ------------------------------------------------------------------



// The Path_2 values are mentioned in Comments beside the delay commands, ones to be changed, to make the robot/turtle reach the GOAL ...
// and they are indicated by '##'
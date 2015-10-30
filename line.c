/*
 * line.c
 *
 * Created: 17-10-2013 21:54:26
 *  Author: Som Prabh Sharma
 */ 

#include <avr/io.h>
#include "util/delay.h"
#define ls2 ((PINA)&(0x01))                  //sensor at pa0 to pa3 from ls2 to rs2
#define ls1 ((PINA)&(0x02))                  // connect motar at port D
#define rs1 ((PINA)&(0b00000100))             //connect sensor at port A
#define rs2 ((PINA)&(0b00001000))
#define ms  ((PINA)&(0b00010000))

char turn=0,i=0,j=0,k=0,x=0,y=0,r=0,l=0,s=0,a=0,b=0,c=0,d=0,p=0,q=0,x1=0,x2=0,y2=0,x4=0,y4=0,x3=0,y3=0;
int A[4];
char  fx=0,fy=2;

void stop()
{   
	while(1)
	{
		PORTD=0x00;
	}
}
void forward()
{
	PORTD=0b00001001; 
}
void backward()
{
	PORTD=0b00000110;
}
void left()
{
	PORTD=0b00001010;
}

void right()
{
	PORTD=0b00000101;
}
void ledoff_1()
{
	PORTB=0x00;
}
void ledon_1()
{
	 k=(i-1)+j;
	 PORTB=((PORTB)|(1<<k));
}
	
void rightsense_1()
{	
	if ((rs2!=0)||(rs2!=0)&&(rs1!=0))                           //move right
	  {  
          forward();
         _delay_ms(10);
		 if((rs2!=0)||(rs2!=0)&&(rs1!=0))
		 {	  
			_delay_ms(170);
			follow();
			if ((ms==0)&&(rs1==0)&&(rs2==0)&&(ls1==0)&&(ls2==0))
		     {
				 _delay_ms(30);
				follow();
				if((ms==0)&&(rs1==0)&&(rs2==0)&&(ls1==0)&&(ls2==0))
				{
					_delay_ms(40);
				
				if((ms==0)&&(rs1==0)&&(rs2==0)&&(ls1==0)&&(ls2==0)) 
		     	 {
					_delay_ms(180);
			      while(ms==0)
		           {  
				     right(); 
					 if (turn>1)
					 {
						 pattern();	 
					 }
					 else
					 {	 
					 }
					 ledoff_1();
					 k=0;
					 j=0;
					 i=0;
					 x=0;
					 y=0;
			        }
					follow();
			   turn++;
			   }
			}			   
			 }			   			   
	            else          //it is strip in right side
				{	
	               follow();
	               j++;
				   x++;
	               
	               ledon_1();
					_delay_ms(50);	
				}
		 } 
	}		 	        	   				   
}

void leftsense_1()
{
	if ((ls2!=0)||((ls2!=0)&&(ls1!=0)))                            //move left
	     {  
			 _delay_ms(10);
          forward(); 
		 if((ls2!=0)||((ls2!=0)&&(ls1!=0)))
		 {	 
			_delay_ms(170);
			follow();
			if ((ms==0)&&(ls1==0)&&(ls2==0)&&(rs1==0)&&(rs2==0))
		     {
				 _delay_ms(30);
				 follow();
				 if((ms==0)&&(rs1==0)&&(rs2==0)&&(ls1==0)&&(ls2==0))
				 {
					 _delay_ms(40); 
				 if((ms==0)&&(rs1==0)&&(rs2==0)&&(ls1==0)&&(ls2==0))
			 {
			 _delay_ms(180);
			      while(ms==0)
		           { 
				     left();
					 ledoff_1();
					  if (turn>1)
					 {
						 pattern();	 
					 } 
					  else
					 {
						 
					 } 
					 i=0;
					 j=0;
					 k=0;
					 x=0;
					 y=0;
			        }
					follow();
			   turn++;
			 } 
			 }	
			 }			 
			 else          // it is strip in left side
			 {
				 follow();
				 i++;
				 y++;
				 _delay_ms(50);
	
			 }
			 
		}	    
	
	}	
	
}

void follow()
{
	forward();
		
	if ((ls1!=0)||((ls1!=0)&&(ms==0)))
	{
		PORTD=0b00001000;
	}
	if ((rs1!=0)||((rs1!=0)&&(ms==0)))
	{
		PORTD=0b00000001;
	}
}

void pattern()
{
	if (x>y)
	{
		r++;
		A[p]=1; 
		p++;           // 1 is for right
		
	}
	else if (x<y)
	{
		l++;
		A[p]=3;            // 3 is for left
		p++;
		
	}
	else if (x==y)
	{
		s++;
		A[p]=2;
		p++;             //2 is for forward
	}
	else
	{
		
	}
	
}

void second_cordnt()
{   
	
	x1=r;
	x4=s;
	y4=l;
	x2=(x1+x4);
	y2=y4;
}

void part_1()
{
	
	follow();
	
	if ((ls2==0)&&(ls1==0)&&(rs1==0)&&(rs2==0))
	{    
		   
		   follow();                     //move forward
	}
	//call part2
	if ((rs2!=0)||((rs2!=0)&&(ls2!=0)))
	{
		_delay_ms(20);
		if ((ls2!=0)||((rs2!=0)&&(ls2!=0)))            //confrm it is grid 
		{    
              if(turn==4)
			  {     
                 pattern();                   //necessary work fir turn=4 
			    }                    //call main function of part 2                 
			
			 grid();
		}
	}
	
	rightsense_1();
	leftsense_1();
	
	//update coordinate at each turn
	if (turn==1)
	{
		a=x+y;
		
		
	}
	else if (turn==2)
	{
		b=x+y;
		
	}
	else if (turn==3)
	{
		c=x+y;
		
		
	}		 
	else if (turn==4)
	{
		d=x+y;
		
		
	}		          
	else
	{
		
	}
}

int main(void)
{
	DDRA=0x00;        //define input for sensors
	PORTA=0xFF;       //pull up
	DDRD=0xFF;        //define output for sensors
	DDRB=0xFF;         //define output for led

    while(1)
    {
      part_1();
	  //forward();
	   
	   
    }
}
//second part
void grid()
{
	
	second_cordnt();
	check_1();
}
void check_1()
{
	if ((rs2!=0)||((rs2!=0)&&(ls2!=0)))
	{
		_delay_ms(20);
		if ((ls2!=0)||((rs2!=0)&&(ls2!=0)))            
		{ 
	            if (A[q]==1)                     //r
	               {
		             fy++;
		             q++;
					 right_2();
					 check_2();
	               }
	           else if (A[q]==2)                   //s
	              {
					  check_1();
	                	fx++;
		                 q++;
						 follow();
						 
	              }
	           else if (A[q]==3)                    //l
	             {
		            fy--;
		            q++;
					left_2();
					check_3();
					
	             }
				 else
				 {		 
					 
				 }					 
        }
		
	}
	
}

void check_2()
{
	if ((rs2!=0)||((rs2!=0)&&(ls2!=0)))
	{
		_delay_ms(20);
		if ((ls2!=0)||((rs2!=0)&&(ls2!=0)))            
		{ 
			if (A[q]==3)         //l
			{
				fx++;
				q++;
				left_2();
				check_1();
				
			}
			else if (A[q]==2)       //s
			{
				fy++;
			
				q++;
				follow();
			check_2();
			
			}
			else
			{
				
			}
			
		}
	}					
	
}	
void check_3()
{
	if ((rs2!=0)||((rs2!=0)&&(ls2!=0)))
	{
		_delay_ms(20);
		if ((ls2!=0)||((rs2!=0)&&(ls2!=0)))            
		{ 
			if(A[q]==1)        //r
	          {
				  fx++;
				  q++;
				  right_2();
				  check_1();
				  
			  }
			  else if (A[q]==2)           //s
			  {
				  fy--;
				  q++;
				  follow();
				  check_3();
			  }
			  else
			  {
				  
			  }
			  if (q==4)
			  {
                    ledon_2();                           //call function for glow led				  
			  }
			  else
			  {
				  
			  }
			  
		}
	}					  
}		

void right_2()
{
	follow();
	_delay_ms(430);
	while(ms==0)
	{
		right();
	}
	
}
void left_2()
{
	follow();
	_delay_ms(430);
	while(ms==0)
	{
		left();
	}
}
void ledon_2()
{
	
	if (ms==0)
	{
		x3=c;
	}
	else
	{
		x3=0;
		PORTB=0b00010000;         //   connect white led at pb4
	}
}
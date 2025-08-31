#include <mega32.h>
#include <stdio.h>
#include <alcd.h>

int H=0;
int M=0;
int S=0;
int h=0;
int m=0;
int sec=0;
int t=0;
int flag_set = 0;
int t_set = 0;
int flag_right = 0;
int t_right = 0;
int flag_up=0;
int  t_up=0;
unsigned int  t_B=0;//**
char str[17];


enum type {state1 ,//CLOCK
           state2 ,//-- , H
           state3 ,//     -- ,M
           state4 ,//         -- ,S
           state5 ,//alarm  --,h
           state6 ,// alarm    -- ,m
           state7 ,// alarm        -- ,s
           state8 ,// active alarm + check  
           state9 ,// TURN OFF THE B  
           }mode;

// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
t++;
t_set++;
t_right++;//**
t_up++;
t_B++;

}


void main(void)
{
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);



// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: CTC top=OCR0
// OC0 output: Disconnected
// Timer Period: 1 ms
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (1<<WGM01) | (0<<CS02) | (1<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x7C;


TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;



// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<OCIE0) | (0<<TOIE0);
lcd_init(16);

// Global enable interrupts
#asm("sei")

DDRA=0x00;  //Pb
PORTA=0xFF; //pull up
DDRD=0XFF;//LED
while (1)
      {
       
             
                   
      switch(mode){
           
       
           case state1:
           lcd_gotoxy(0,0);
           sprintf(str,"%02d : %02d  : %02d" , H,M,S);
           lcd_puts(str);//**
           if (t>999){
           t=0;//**
           S++;
           }
           if (S>59){
           S=0;
           M++;
           }
           if (M>59){
           M=0;
           H++;
           }
             
             if ( flag_set == 0) {
                 
                  if (PINA.0 == 0){
                        flag_set = 1;
                        t_set = 0;
                       
                    }
                }

                else {
                      if (t_set >29){
                       if (PINA.0 == 0)
                         t_set = 0;
                         else{
                            mode=state2;
                            lcd_clear();
                            flag_set=0;
                           
                           
                        }
                     
                      }
               
                }
               
               
               
                   
                   
                    if(flag_right==0){
                    if(PINA.1==0){
                        flag_right=1;
                        t_right=0;
                    }
                }
                else{
                    if(t_right>5){
                        if(PINA.1==0)
                            t_right=0;
                        else{
                            mode=state8;
                            lcd_clear();
                            flag_right=0;///************
                        }
                    }
                }        
               
               
                       
                 
                break;
                /////////////////////////////////// //-- , H
case state2 :
                lcd_gotoxy(0,0);
                sprintf(str,"%02d : %02d  : %02d  S" , H,M,S);
                lcd_puts(str);//**
               
                lcd_gotoxy(0,1);
                lcd_putsf("--");  
               
                if(flag_right==0){
                    if(PINA.1==0){
                        flag_right=1;
                        t_right=0;
                    }
                }
                else{
                    if(t_right>29){
                        if(PINA.1==0)
                            t_right=0;
                        else{
                            mode=state3;
                            lcd_clear();
                            flag_right=0;
                        }
                    }
                }
               
                if (flag_up==0){
                 if (PINA.2 == 0){
                            flag_up = 1;
                            t_up = 0;
                           
                        }
                    }

                    else {
                          if (t_up >29){
                           if (PINA.2 == 0)
                             t_up = 0;
                             else{
                                H++;
                                if (H>23)
                                H=00;
                                flag_up=0;
                               
                               
                            }
                         
                          }
                       }
                   
                    if ( flag_set == 0) {
                 
                  if (PINA.0 == 0){
                        flag_set = 1;
                        t_set = 0;
                       
                    }
                }

                else {
                      if (t_set >29){
                       if (PINA.0 == 0)
                         t_set = 0;
                         else{
                            mode=state5;
                            lcd_clear();
                            flag_set=0;
                           
                           
                        }
                     
                      }
               
                }
               
               
                break;
                //////////////////////////////////// //     -- ,M
  case state3 :
                lcd_gotoxy(0,0);
                sprintf(str,"%02d : %02d  : %02d  S" , H,M,S);
                lcd_puts(str);//**
               
                lcd_gotoxy(5,1);//**
                lcd_putsf("--");  
                 
               
                if(flag_right==0){
                    if(PINA.1==0){
                        flag_right=1;
                        t_right=0;
                    }
                }
                else{
                    if(t_right>29){
                        if(PINA.1==0)
                            t_right=0;
                        else{
                            mode=state4;
                            lcd_clear();
                            flag_right=0;
                        }
                    }
                }
               
                if (flag_up==0){
                 if (PINA.2 == 0){
                            flag_up = 1;
                            t_up = 0;
                           
                        }
                  }

                    else {
                          if (t_up >29){
                           if (PINA.2 == 0)
                             t_up = 0;
                             else{
                                M++;
                                if (M>59)
                                M=00;
                                flag_up=0;
                               
                               
                            }
                         
                          }
                   
                       }
                       
                     if ( flag_set == 0) {
                 
                  if (PINA.0 == 0){
                        flag_set = 1;
                        t_set = 0;
                       
                    }
                }

                else {
                      if (t_set >29){
                       if (PINA.0 == 0)
                         t_set = 0;
                         else{
                            mode=state5;
                            lcd_clear();
                            flag_set=0;
                           
                           
                        }
                     
                      }
               
                }  
               
                 break;
                ////////////////////////////////////////         -- ,S
case state4 :
                lcd_gotoxy(0,0);
                sprintf(str,"%02d : %02d  : %02d  S" , H,M,S);
                lcd_puts(str);//**
               
               
                lcd_gotoxy(11,1); //**
                lcd_putsf("--");  
               
                if(flag_right==0){
                    if(PINA.1==0){
                        flag_right=1;
                        t_right=0;
                    }
                }
                else{
                    if(t_right>29){
                        if(PINA.1==0)
                            t_right=0;
                        else{
                            mode=state2;
                            lcd_clear();
                            flag_right=0;
                        }
                    }
                }
                 
                 if (flag_up==0){
                  if (PINA.2 == 0){
                            flag_up = 1;
                            t_up = 0;
                           
                        }
                    }

                    else {
                          if (t_up >29){
                           if (PINA.2 == 0)
                             t_up = 0;
                             else{
                                S++;
                                if (S>59)
                                S=00;
                                flag_up=0;
                               
                               
                            }
                         
                          }
                   
                        }
                       
                     if ( flag_set == 0) {
                 
                  if (PINA.0 == 0){
                        flag_set = 1;
                        t_set = 0;
                       
                    }
                }

                else {
                      if (t_set >29){
                       if (PINA.0 == 0)
                         t_set = 0;
                         else{
                            mode=state5;
                            lcd_clear();
                            flag_set=0;
                           
                           
                        }
                     
                      }
               
                }  
               
                 break;
    ///////////////////////////////////alarm  --,h
                case state5:
                 
                 lcd_gotoxy(0,0);
                 sprintf(str,"%02d : %02d  : %02d  A" , h,m,sec);
                 lcd_puts(str);//**
                 
                lcd_gotoxy(0,1);
                lcd_putsf("--");  
               
                if(flag_right==0){
                    if(PINA.1==0){
                        flag_right=1;
                        t_right=0;
                    }
                }
                else{
                    if(t_right>29){
                        if(PINA.1==0)
                            t_right=0;
                        else{
                            mode=state6;
                            lcd_clear();
                            flag_right=0;
                        }
                    }
                }
               
                if (flag_up==0){
                 if (PINA.2 == 0){
                            flag_up = 1;
                            t_up = 0;
                           
                        }
                    }

                    else {
                          if (t_up >29){
                           if (PINA.2 == 0)
                             t_up = 0;
                             else{
                                h++;
                                if (h>23)
                                h=0;
                                flag_up=0;
                               
                               
                            }
                         
                          }
                       }
                       
                 if ( flag_set == 0) {
                 
                  if (PINA.0 == 0){
                        flag_set = 1;
                        t_set = 0;
                       
                    }
                }

                else {
                      if (t_set >29){
                       if (PINA.0 == 0)
                         t_set = 0;
                         else{
                            mode=state1;
                            lcd_clear();
                            flag_set=0;
                            t = 0; //*******
                           
                           
                        }
                     
                      }
               
                }
                break;
                ////////////////////////////////// alarm    -- ,m
case state6:
                lcd_gotoxy(0,0);
                sprintf(str,"%02d : %02d  : %02d  A" , h,m,sec);
                lcd_puts(str);//**
               
                lcd_gotoxy(5,1);//**
                lcd_putsf("--");  
                 
               
                if(flag_right==0){
                    if(PINA.1==0){
                        flag_right=1;
                        t_right=0;
                    }
                }
                else{
                    if(t_right>29){
                        if(PINA.1==0)
                            t_right=0;
                        else{
                            mode=state7;
                            lcd_clear();
                            flag_right=0;
                        }
                    }
                }
               
                if (flag_up==0){
                 if (PINA.2 == 0){
                            flag_up = 1;
                            t_up = 0;
                           
                        }
                  }

                    else {
                          if (t_up >29){
                           if (PINA.2 == 0)
                             t_up = 0;
                             else{
                                m++;
                                if (m>59)
                                m=0;
                                flag_up=0;
                               
                               
                            }
                         
                          }
                   
                       }
                       
                     if ( flag_set == 0) {
                 
                  if (PINA.0 == 0){
                        flag_set = 1;
                        t_set = 0;
                       
                    }
                }

                else {
                      if (t_set >29){
                       if (PINA.0 == 0)
                         t_set = 0;
                         else{
                            mode=state1;
                            lcd_clear();
                            flag_set=0;
                            t = 0;//*****
                           
                           
                        }
                     
                      }
               
                }  
                break;
case state7:
                lcd_gotoxy(0,0);
                sprintf(str,"%02d : %02d  : %02d  A" , h,m,sec);
                lcd_puts(str);//**
               
               
                lcd_gotoxy(11,1); //**
                lcd_putsf("--");  
               
                if(flag_right==0){
                    if(PINA.1==0){
                        flag_right=1;
                        t_right=0;
                    }
                }
                else{
                    if(t_right>29){
                        if(PINA.1==0)
                            t_right=0;
                        else{
                            mode=state5;
                            lcd_clear();
                            flag_right=0;
                        }
                    }
                }
                 
                 if (flag_up==0){
                  if (PINA.2 == 0){
                            flag_up = 1;
                            t_up = 0;
                           
                        }
                    }

                    else {
                          if (t_up >29){
                           if (PINA.2 == 0)
                             t_up = 0;
                             else{
                                sec++;
                                if (sec>59)
                                sec=0;
                                flag_up=0;
                               
                               
                            }
                         
                          }
                   
                        }
               
                   
                   
                     if ( flag_set == 0) {
                 
                  if (PINA.0 == 0){
                        flag_set = 1;
                        t_set = 0;
                       
                    }
                }

                else {
                      if (t_set >29){
                       if (PINA.0 == 0)
                         t_set = 0;
                         else{
                            mode=state1;
                            lcd_clear();
                            flag_set=0;
                            t = 0; //******
                           
                           
                        }
                     
                      }
               
                }
               
                break;
               
               
               
             /////////////////////////////////////////// active alarm + check
case state8:
               lcd_gotoxy(0,0);
               sprintf(str,"%02d : %02d  : %02d" , H,M,S);
               lcd_puts(str);//**
               if (t>999){
               t=0;//**
               S++;
               }
               if (S>59){
               S=0;
               M++;
               }
               if (M>59){
               M=0;
               H++;
               }  
                lcd_gotoxy(15,0);
                lcd_putsf("A");
               
                   if ((h > 0) && (m > 0) && (sec > 0)) {  
                     if ((H == h) && (M == m) && (S == sec)) {
                      PORTD.6=1;    // turn B on
                       t_B = 0;
                       
                    }  
                   }
                   
                   if ((PORTD.6 == 1) && (t_B >= 60000)) {
                   t_B = 0;
                   PORTD.6 = 0; // turn B off
                   }
                   
                   
                  if (flag_up==0){
                  if (PINA.2 == 0){
                            flag_up = 1;
                            t_up = 0;
                           
                        }
                    }

                    else {
                          if (t_up >29){
                           if (PINA.2 == 0)
                             t_up = 0;
                             else{
                                mode=state9;
                               
                                flag_up =0;
                           
                               
                               
                            }
                         
                          }
                   
                        }
                           
                           
                 
                 
                  if ( flag_set == 0) {
                 
                  if (PINA.0 == 0){
                        flag_set = 1;
                        t_set = 0;
                       
                    }
                }

                else {
                      if (t_set >49){
                       if (PINA.0 == 0)
                         t_set = 0;
                         else{
                            mode=state1;
                            lcd_clear();
                            flag_set=0;
                           
                           
                        }
                     
                      }
               
                }        
                     
                break;
                ////////////////////////////////// TURN OFF THE B
case state9:
                PORTD.6=0;
                lcd_gotoxy(0,0);
                sprintf(str,"%02d : %02d  : %02d" , H,M,S);
                lcd_puts(str);//**
                if (t>999){
                 t=0;//**
               S++;
               }
               if (S>59){
               S=0;
               M++;
               }
               if (M>59){
               M=0;
               H++;
               }
                 if(flag_right==0){
                    if(PINA.1==0){
                        flag_right=1;
                        t_right=0;
                    }
                }
                else{
                    if(t_right>5){
                        if(PINA.1==0)
                            t_right=0;
                        else{
                            mode=state1;
                            lcd_clear();
                            flag_right=0;///************
                        }
                    }
                }        
               
               
                break;    
               
           }//switch
           
      } //while
     
} //main 

/* 
 * File:   application.c
 * Author: Marwan Mohamed
 *
 * Created on August 23, 2023, 1:49 PM
 */

#include"application.h"
/*
 * 
 */




int main(){
 label1:application_intialize();
 Welcome_massage();
    while(1){
Std_return_typ ret = EN_ok;
uint8 oparand_1[6] ;
memset(oparand_1,'\0',6);
uint8 oparand=0xff;
sint32 num[8]={0};
uint8 operator[8]={0};
uint8 operator_eq=0;
float32 result=0;
uint8 txt[11];
uint8 counter=0,counter_operand=0,counter1=1; 
while(1){
    while(1){
      do{
        	 ret=KEYPAD_READ_uint8(&keypad,&oparand);
              __delay_ms(150);
		
    	} while(oparand==0xff);
        if(oparand=='#'||((counter==0)&&(oparand=='='||oparand=='+'||oparand=='*'||oparand=='/'))) /*newline@26/10/2023*//*adding a algorithm to prevent conflict in operation for frist time if operator is (*,+,/) funcation*/
        {
            LCD_4BITS_SEND_COMMAN(&lcd_4b,CMM_LCD_CLEAR);
            goto label1;
        }
        else if(((counter!=0)&&oparand=='='))
        {
            operator_eq=oparand;
            ret=LCD_4BITS_SEND_DATA(&lcd_4b,operator_eq);
            ret=LCD_4BITS_SEND_DATA_POS(&lcd_4b,1,counter1,operator_eq);
            oparand=0xff;
            counter1++;
            break;
        }
        else if(oparand=='+'||oparand=='*'||oparand=='/'&&counter!=0||((counter!=0)&&oparand=='-'))
        {
        operator[counter_operand]=oparand;
        ret=LCD_4BITS_SEND_DATA(&lcd_4b,operator[counter_operand]);
        ret=LCD_4BITS_SEND_DATA_POS(&lcd_4b,1,counter1,operator[counter_operand]);
        oparand=0xff;
        counter1++;
        break;
		
        }else
        {
		ret=LCD_4BITS_SEND_DATA(&lcd_4b,oparand);
        ret=LCD_4BITS_SEND_DATA_POS(&lcd_4b,1,counter1,oparand);
         oparand_1[counter]=oparand;
          counter++;
        }
      
        oparand=0xff;
        counter1++;
        __delay_ms(150);
        }
    num[counter_operand]=customAtoi(oparand_1,counter);
      
    counter_operand++;
     oparand=0xff;
    memset(oparand_1,'\0',6);
    counter=0;
    if(operator_eq=='=')
    {
        break;
    }
}


 
    
	if(operator_eq == '=')
	{
        uint8 counter2=0;
        result=num[counter2];
        for(counter2=0;counter2<counter_operand;counter2++){
         switch(operator[counter2]){
             case '+':
                result+= num[counter2+1];
                break;
              case '-':
                result-= num[counter2+1];
                break;  
              case '*':
                result*=num[counter2+1]; 
                break;
                case '/':
                    if(num[counter2+1] != 0){
                        result/=(float32)num[counter2+1];
                    }
                    else{
                        ret=LCD_4BITS_SEND_STRING_POS(&lcd_4b,2,5,"math error!!");
                        goto label2;
                    }
                    break;
         }
         
        }       
        if(result == (int)result){
           convert_sint32_to_string(result,txt);
        }
        else
        {
            convert_floating_32_to_string(result,txt);
        }
        ret=LCD_4BITS_SEND_STRING(&lcd_4b,txt);
        ret=LCD_4BITS_SEND_STRING_POS(&lcd_4b,1,counter1,txt);
        /*newline@26/10/2023*//*adding a round funcation*/
        if(result == (int)result){
         convert_sint32_to_string(result,txt);
         }
         else
         {
            convert_floating_32_to_string(round(result),txt);
         }
        /*newline@26/10/2023*//*adding a round funcation*/
          ret=LCD_4BITS_SEND_STRING_POS(&lcd_4b,4,18,txt);
		label2:;
    }else
	{
        LCD_4BITS_SEND_COMMAN(&lcd_4b,CMM_LCD_CLEAR);
		 break;
		
	}
       
     __delay_ms(1000);   
    loading();
    
 
  }
 return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_return_typ ret = EN_ok;
    ret=ecu_intialize();
}
void Welcome_massage(void){
    uint8 counter=zero_intial;
    for(counter=zero_intial;counter<limit_repeat;counter++){
        LCD_4BITS_SEND_STRING_POS(&lcd_4b,2,8,"WELCOME");
        __delay_ms(500);
        LCD_4BITS_SEND_COMMAN(&lcd_4b,CMM_LCD_CLEAR);
        __delay_ms(100);

    }    
}
void loading(void){
    __delay_ms(100);
     LCD_4BITS_SEND_COMMAN(&lcd_4b,CMM_LCD_CLEAR);
         __delay_ms(100);

     LCD_4BITS_SEND_STRING_POS(&lcd_4b,2,4,"loading");
    uint8 counter=zero_intial;
    for(counter=zero_intial;counter<2;counter++){
        uint8 counterl=0;
        for(counterl=11;counterl<16;counterl++){
             LCD_4BITS_SEND_DATA_POS(&lcd_4b,2,counterl,'.');
            __delay_ms(50);
        }   
    LCD_4BITS_SEND_STRING_POS(&lcd_4b,2,11,"     ");
    }
    LCD_4BITS_SEND_COMMAN(&lcd_4b,CMM_LCD_CLEAR);
    __delay_ms(100);
}
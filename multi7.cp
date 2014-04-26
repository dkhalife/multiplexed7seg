#line 1 "C:/Users/Dan/Desktop/Multiplexed 7-Seg/multi7.c"
#line 13 "C:/Users/Dan/Desktop/Multiplexed 7-Seg/multi7.c"
const unsigned int _pA=0b00000001;
const unsigned int _pB=0b00000010;
const unsigned int _pC=0b00000100;
const unsigned int _pD=0b00001000;
const unsigned int _pE=0b00010000;
const unsigned int _pF=0b00100000;
const unsigned int _pG=0b01000000;
const unsigned int _pH=0b10000000;

int i,j,k;
unsigned int D1,D2,D3,D4;
const int DELAY=200;




unsigned char Display(unsigned char no){
 unsigned char Pattern;
 unsigned char SEGMENT[]={
 0xFF&(~_pG)&(~_pH),
 _pB|_pC,
 0xFF&(~_pC)&(~_pF)&(~_pH),
 0xFF&(~_pE)&(~_pF)&(~_pH),
 _pB|_pC|_pF|_pG,
 0xFF&(~_pB)&(~_pE)&(~_pH),
 0xFF&(~_pB)&(~_pH),
 _pA|_pB|_pC,
 0xFF&(~_pH),
 0xFF&(~_pE)&(~_pH),
 };
 Pattern=SEGMENT[no];
 return(Pattern);
}






void Light_show(int D1, int D2, int D3, int D4){
 PORTD=0x01;
 PORTB=Display(D1);
 DELAY_ms(DELAY);

 PORTD=0x02;
 PORTB=Display(D2);
 Delay_ms(DELAY);

 PORTD=0x04;
 PORTB=Display(D3);
 Delay_ms(DELAY);

 PORTD=0x08;
 PORTB=Display(D4);
 Delay_ms(DELAY);
}





void Display_nbr(int v){

 D1=(v-v%1000)/1000;
 v=v-D1*1000;
 D2=(v-v%100)/100;
 v=v-D2*100;
 D3=(v-v%10)/10;
 v=v-D3*10;
 D4=v;
 Light_show(D1,D2,D3,D4);
}

void main() {









 OSCCON=0x6E;





 CMCON=0x07;










 ADCON1=0x8F;








 TRISB=0x00;
 TRISD=0x00;




 while(1){
 j=0;
 while(j<50){
 for(i=0; i<10000; i++){
 Display_nbr(i);
 }
 Delay_ms(1);
 j++;
 }
 }
}

//**  Configuration :
//      7Seg = Bit
//        a  =  2      |  0
//        b  =  3      |  1
//        c  =  6      |  2
//        d  =  5      |  3
//        e  =  4      |  4
//        f  =  1      |  5
//        g  =  0      |  6
//       dip =  7      |  u
//**

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

//**
//  Number to 7-Seg:
//**
unsigned char Display(unsigned char no){
    unsigned char Pattern;
    unsigned char SEGMENT[]={
		0xFF&(~_pG)&(~_pH),              // 0 = All but G and H
		_pB|_pC,                         // 1 = B and C
		0xFF&(~_pC)&(~_pF)&(~_pH),       // 2 = All but C, F and H
		0xFF&(~_pE)&(~_pF)&(~_pH),       // 3 = All but E, F and H
		_pB|_pC|_pF|_pG,                 // 4 = B, C, F and G
		0xFF&(~_pB)&(~_pE)&(~_pH),       // 5 = All but B, E and H
		0xFF&(~_pB)&(~_pH),              // 6 = All but B and H
		_pA|_pB|_pC,                     // 7 = A, B and C
		0xFF&(~_pH),                     // 8 = All but H
		0xFF&(~_pE)&(~_pH),              // 9 = All but H
    };
    Pattern=SEGMENT[no];
    return(Pattern);
}

//**
//  7-Seg Illusion effect
//  Inputs: Digits D1,D2,D3,D4
//  Logic dps: Digits BT1,BT2,BT3,BT4
//**
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

//**
//  Number to digits
//  Input type : Int
//**
void Display_nbr(int v){
	// Get only 4 digits
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
	//**
	//  Oscillator Configuration:
	//  0b0
	//  - 4 MHz (110)
	//  - Primary system clock (1)
	//  - Stable frequency (1)
	//  - System clock : Internal RC (10)
	//  - Total : 0b01101110
	//**
	OSCCON=0x6E;
	//**
	//  Comparator Configuration:
	//  Disable all
	//  - Total : 0b00000111;
	//**
	CMCON=0x07;
	//**
	//  A/D Configuration:
	//  0b
	//  Left Justified (1)
	//  A/D Clock divide by 2 disabled (0)
	//  VRef - = VSS (0)
	//  VRef + = VDD (0)
	//  - All Digital (1111)
	//  - Total : 0b10001111;
	//**
	ADCON1=0x8F;
	//**
	//  PORT Directions
	//  - Output:
	//    + PORTB
	//    + PORTD
	//  - Input:
	//    + PORTA
	//**
	TRISB=0x00;
	TRISD=0x00;
	
	//**
	//  Main Program
	//**
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

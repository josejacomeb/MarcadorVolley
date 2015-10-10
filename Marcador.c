/*Marcador Ecuavolley -  Autor: José Jácome*/
#include <16F628A.h>
#fuses XT, NOWDT
#use delay (clock = 4M)
#use fast_io(A)
#use fast_io(B)
#define RD1 PIN_B0
#define RD2 PIN_B1
#define RD3 PIN_B2
#define RD4 PIN_B3
#define CLK PIN_B4
#define RST PIN_B5
void mostrar();
void inicializar();
//Variables
int u1 = 2;
int u2 = 0;
int d1 = 0;
int d2 = 0;

int1 cero[7] = {0,1,0,0,0,0,0};
int1 uno[7] = {1,1,1,1,0,0,1};
int1 dos[7] = {0,1,0,0,1,0,0};
int1 tres[7] = {0,1,0,0,0,0,0};
int1 cuatro[7] = {0,0,1,1,0,0,1};
int1 cinco[7] = {0,0,1,0,0,1,0};
int1 seis[7] = {0,0,0,0,0,1,1};
int1 siete[7] = {1,1,1,1,0,0,0};
int1 ocho[7] = {0,0,0,0,0,0};
int1 nueve[7] = {0,0,1,0,0,0};

void main(){
   set_tris_a(0x3F);      //Entrada por el Puerto A(A0,A1,A2,A3,A5)
   set_tris_b(0x00);
   output_a(0xFF);
   output_b(0xFF);
   inicializar();
   delay_ms(500);
   mostrar();
}
void mostrar(){
   Signed int i = 0;
   for(i = 8;i>=0;i--){
      output_low(CLK);
      delay_ms(150);
      if(i==8){
         output_low(RD1);
         output_low(RD2);
         output_low(RD3);
         output_low(RD4);
      }
      else{
         if(u1 == 0){
            if(cero[7-i]== 0)
               output_low(RD1);
            else
               output_high(RD1);
         }
         else if(u1 == 1){
            if(uno[7-i]== 0)
               output_low(RD1);
            else
               output_high(RD1);
         }
         else if(u1 == 2){
            if(dos[7-i]== 0)
               output_low(RD1);
            else
               output_high(RD1);
         }
         else if(u1 == 3){
            if(tres[7-i]== 0)
               output_low(RD1);
            else
               output_high(RD1);
         }
         else if(u1 == 4){
            if(cuatro[7-i]== 0)
               output_low(RD1);
            else
               output_high(RD1);
         }
         else if(u1 == 5){
            if(cinco[7-i]== 0)
               output_low(RD1);
            else
               output_high(RD1);
         }
         else if(u1 == 6){
            if(seis[7-i]== 0)
               output_low(RD1);
            else
               output_high(RD1);
         }
         else if(u1 == 7){
            if(siete[7-i]== 0)
               output_low(RD1);
            else
               output_high(RD1);
         }
         else if(u1 == 8){
            if(ocho[7-i]== 0)
               output_low(RD1);
            else
               output_high(RD1);
         }
         else{
            if(nueve[7-i]== 0)
               output_low(RD1);
            else
               output_high(RD1);
         }


      }
      output_high(CLK);
      delay_ms(150);
   }
}
void inicializar(){
   int i = 0;
   for(i=0;i<=8;i++){
      output_low(CLK);
      delay_ms(150);
      if(i==0){
         output_low(RD1);
         output_low(RD2);
         output_low(RD3);
         output_low(RD4);
      }
      else{
         output_high(RD1);
         output_high(RD2);
         output_high(RD3);
         output_high(RD4);
      }
      output_high(CLK);
      delay_ms(150);
   }
}


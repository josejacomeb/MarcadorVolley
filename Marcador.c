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
#define EN PIN_A0
void mostrar();
void inicializar();
void desplazamiento(int dato, int posicion);
//Donde se almacena el score
int8 marcador[4]={9,6,7,8};
//Código para Formar los Numeros
int1 cero[7] = {1,0,0,0,0,0,0};
int1 uno[7] = {1,1,1,1,0,0,1};
int1 dos[7] = {0,1,0,0,1,0,0};
int1 tres[7] = {0,1,1,0,0,0,0};
int1 cuatro[7] = {0,0,1,1,0,0,1};
int1 cinco[7] = {0,0,1,0,0,1,0};
int1 seis[7] = {0,0,0,0,0,1,1};
int1 siete[7] = {1,1,1,1,0,0,0};
int1 ocho[7] = {0,0,0,0,0,0};
int1 nueve[7] = {0,0,1,0,0,0};
//Variables Auxiliares
Signed int8 i = 0;
int8 j = 0;
void main(){
   set_tris_a(0b00111110);      //Entrada por el Puerto A(A0,A1,A2,A3,A5) 00111111
   set_tris_b(0x00);
   output_a(0x3F);
   output_b(0xFF);
   output_low(EN);
   inicializar();
   output_high(EN);
   delay_ms(1500);
   mostrar();
   delay_ms(5000);

}
void mostrar(){
   output_low(EN);   //Deshabilita el Muestreo del Display
   for(i = 7;i>=0;i--){
      output_low(CLK);   //Envia la Señal de Reloj a 0 aceptar el Desplazamiento
      delay_ms(150);
      for(j = 0;j<=3;j++){
         if(i==7){         //Añadir Código de Set Después
            output_low(RD1);
            output_low(RD2);
            output_low(RD3);
            output_low(RD4);
         }
         else{
            if(marcador[j] == 0){
               desplazamiento(cero[6-i],j);
            }
            else if(marcador[j] == 1){
               desplazamiento(uno[6-i],j);
            }
            else if(marcador[j] == 2){
               desplazamiento(dos[6-i],j);
            }
            else if(marcador[j] == 3){
               desplazamiento(tres[6-i],j);
            }
            else if(marcador[j] == 4){
               desplazamiento(cuatro[6-i],j);
            }
            else if(marcador[j] == 5){
               desplazamiento(cinco[6-i],j);
            }
            else if(marcador[j] == 6){
               desplazamiento(seis[6-i],j);
            }
            else if(marcador[j] == 7){
               desplazamiento(siete[6-i],j);
            }
            else if(marcador[j] == 8){
               desplazamiento(ocho[6-i],j);
            }
            else {
               desplazamiento(nueve[6-i],j);
            }

         }
      }
      output_high(CLK);   //Realiza el Desplazamiento al Ponerse en 1
      delay_ms(150);
      output_high(EN);      //Habilita la Visualización del Display
   }
}
void inicializar(){
   int i = 0;
   for(i=0;i<8;i++){
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
void desplazamiento(int dato, int posicion){
   if(posicion == 0){
       if(dato== 0)
          output_low(RD1);
       else
          output_high(RD1);
   }
   else  if(posicion == 1){
       if(dato== 0)
          output_low(RD2);
       else
          output_high(RD2);
   }
   else  if(posicion == 2){
       if(dato== 0)
          output_low(RD3);
       else
          output_high(RD3);
   }
   else{
       if(dato== 0)
          output_low(RD4);
       else
          output_high(RD4);
   }
}

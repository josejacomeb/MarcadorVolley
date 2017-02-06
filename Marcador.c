/*Marcador Ecuavolley -  Autor: José Jácome*/
#include <16F628A.h>
#fuses INTRC_IO,NOWDT,NOMCLR
#use delay (clock = 4M)
#use rs232(baud=9600, bits = 8, parity = N, xmit=PIN_B2, rcv=PIN_B1)
#use standard_io(A)
#use standard_io(B)
//Alias para Pines de Desplazamiento
#define RD1 PIN_B0
#define RD2 PIN_A6
#define RD3 PIN_A7
#define RD4 PIN_A4
#define CLK PIN_B4
#define RST PIN_B5
#define BUZZER PIN_A0
//Alias para entradas Digitales
#define Izq PIN_A1
#define Der PIN_A2
#define Reset PIN_A3
#define Subir PIN_A5
//Alias para LEDs de Cambio
#define LEDI PIN_B6
#define LEDD PIN_B7

void mostrar();
void inicializar();
void desplazamiento(int dato, int posicion);
void sumar(int lado);   //Suma del Lado Izquierdo(0) o Derecho (1)
void restar(int lado);   //Resta del Lado Izquierdo(0) o Derecho (1)
//Donde se almacena el score
Signed int8 marcador[4]={0,0,0,0};
//Código para Formar los Numeros
int1 cero[7] = {1,0,0,0,0,0,0};
int1 uno[7] = {1,1,1,1,0,0,1};
int1 dos[7] = {0,1,0,0,1,0,0};
int1 tres[7] = {0,1,1,0,0,0,0};
int1 cuatro[7] = {0,0,1,1,0,0,1};
int1 cinco[7] = {0,0,1,0,0,1,0};
int1 seis[7] = {0,0,0,0,0,1,1};
int1 siete[7] = {1,1,1,1,0,0,0};
int1 ocho[7] = {0,0,0,0,0,0,0};
int1 nueve[7] = {0,0,1,0,0,0,0};
//Variables Auxiliares
Signed int8 i = 0;
int8 j = 0;
//Tope de Puntos
int8 tope1 = 12;
int8 tope2 = 15;
//Muestra el Set Ganado por el equipo
int8 setD = 0;
int8 setI = 0;
//Cambios
short CambioI = 0;
short CambioD = 0;
void main(){
   output_a(0x3F);
   output_b(0xFF);
   printf("Inicio");
   output_low(LEDI);
   output_low(LEDD);
   inicializar();
   mostrar();
   delay_ms(1500);
      while(TRUE){
      if(input(Izq)==0){
         delay_ms(500);
         if(input(Izq)==1){
            putc('s');
            putc('l');
            sumar(0);
         }
         else{
            putc('r');
            putc('l');
            restar(0);
            delay_ms(500);    //Por si acaso se mantiene aplastado
         }
      }
      if(input(Der)==0){
         delay_ms(500);
         if(input(Der)==1){
            sumar(1);
         }
         else{
            restar(1);
            delay_ms(500);    //Por si acaso se mantiene aplastado
         }
      }
   }
}
void mostrar(){
   for(i = 7;i>=0;i--){
      output_low(CLK);   //Envia la Señal de Reloj a 0 aceptar el Desplazamiento
      delay_ms(50);
      for(j = 0;j<=3;j++){
         if(i==7){
            if(setI == 0){
               output_low(RD1);
               output_low(RD2);
            }
            if(setI == 1)
               output_high(RD1);
            if(setI == 2)
               output_high(RD2);
            if(setD == 0){
               output_low(RD3);
               output_low(RD4);
            }
            if(setD == 1)
               output_high(RD3);
            if(setD == 2)
               output_high(RD4);
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
      delay_ms(50);
   }
}
void inicializar(){
   int i = 0;
   for(i=0;i<8;i++){
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
      output_low(CLK);
      output_high(CLK);
      delay_ms(1);
   }
}
//Funcion que hace funcionar al Registro de Desplazamiento 74164
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
void sumar(int lado){
   if(lado==0){
      if(CambioI == 1){
         if(marcador[1]<10){;
           marcador[1] += 1;
         }
         else{
            marcador[1] = 0;
            marcador[0] += 1;
         }
         mostrar();
      }
      else{
         CambioD = 0;
         output_low(LEDD);
         CambioI = 1;
         output_high(LEDI);
      }
   }
   else{
      if(CambioD == 1){
         if(marcador[3]<10){
            marcador[3] += 1;
         }
         else{
            marcador[3] = 0;
            marcador[2] += 1;
         }
         mostrar();
      }
      else{
         CambioI = 0;
         output_low(LEDI);
         CambioD = 1;
         output_high(LEDD);
      }
   }
   //Validar  con el Tope
   if(setI + setD <2){
      if(10*marcador[0]+marcador[1] == tope1 || 10*marcador[2]+marcador[3] == tope1){
         if(lado == 0)
            setI += 1;
         else
            setD += 1;
         marcador[0] = 0;
         marcador[1] = 0;
         marcador[2] = 0;
         marcador[3] = 0;
         mostrar();
      }
   }
   else{
      if(10*marcador[0]+marcador[1] == tope2 || 10*marcador[2]+marcador[3] == tope2 ){
         if(lado == 0)
            setI += 1;
         else
            setD += 1;
         marcador[0] = 0;
         marcador[1] = 0;
         marcador[2] = 0;
         marcador[3] = 0;
         mostrar();
      }
   }
}
void restar(int lado){
   if(lado==0){
      if(marcador[1]>=0){
         marcador[1] -= 1;
      }
      else{
         marcador[1] = 0;
         marcador[0] -= 1;
      }
   }
   else{
      if(marcador[3]>=0){
         marcador[3] -= 1;
      }
      else{
         marcador[3] = 0;
         marcador[2] -= 1;
      }
   }
   mostrar();
}




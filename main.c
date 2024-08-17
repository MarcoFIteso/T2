#include <stdint.h>

#define SIM_5 (*((volatile uint32_t *) 0x40048038))
#define PCR_PTB21 (*((volatile uint32_t *) 0x4004A054))
#define PCR_PTB22 (*((volatile uint32_t *) 0x4004A058))
#define PCR_PTE26 (*((volatile uint32_t *) 0X4004D068))
#define GPIO_B_BASE_ADDR ((volatile uint32_t *) 0x400FF040)
#define GPIO_E_BASE_ADDR ((volatile uint32_t *) 0x400FF100)


typedef struct{
	uint32_t PDOR;
	uint32_t PSOR;
	uint32_t PCOR;
	uint32_t PTOR;
	uint32_t PDIR;
	uint32_t PDDR;
}GPIO_t;

#define GPIO_B ((GPIO_t *) GPIO_B_BASE_ADDR) //Definimos el address de los gpios del puerto b
#define GPIO_E ((GPIO_t *) GPIO_E_BASE_ADDR) //Definimos el address de los gpios del puerto e

int main(void) {
	SIM_5 = 0x00002400; //Activamos el clock de PTE Y PTB
	PCR_PTB22 = 0x00000100; //Seteamos el portb22 en gpio
	PCR_PTB21 = 0x00000100; //Seteamos el portb21 en gpio
	PCR_PTE26 = 0x00000100; //Seteamos el porte26 en gpio
	GPIO_B->PDOR = 0x00600000; //Ponemos los valores en 1 para que no se activen
	GPIO_B->PDDR = 0x00600000; //Ponemos los de los portb 22 y 21 en output
	GPIO_E->PDOR = 0x04000000; //Ponemos el valor del pin 26 pot e en 1 para no activarlo
	GPIO_E->PDDR = 0x04000000; //Ponemos el pin 26 port e en output
	while(1){
		GPIO_B->PDOR = 0x00200000; //Activamos el color rojo
		GPIO_B->PDOR = 0x00400000; //Activamos el color azul
		GPIO_B->PDOR = 0x00600000; //Quitamos los colores rojo y azul
		GPIO_E->PDOR = 0x00000000; //Ponemos el color verde
		GPIO_B->PDOR = 0x00000000; //Ponemos el color blanco
		GPIO_E->PDOR = 0x04000000; //Quitamos el color verde
		GPIO_B->PDOR = 0x00600000; //Quitamos los colores rojo y azul
	}
	return 0;
}


#include <stdio.h>
#include "gpio.h"

typedef struct{
  // Step 3:
  uint32_t unused_A [321];
  uint32_t OUT;
  uint32_t OUTSET;
  uint32_t OUTCLR;
  uint32_t IN;
  uint32_t DIR;
  uint32_t DIRSET;
  uint32_t DIRCLR;
  uint32_t LATCH;
  uint32_t DETECTMODE;
  uint32_t unused_B[118];
  uint32_t PIN_CNF[32];
} gpio_reg_t;

volatile gpio_reg_t* port_zero=  (gpio_reg_t*) (0x50000000);
volatile gpio_reg_t* port_one=  (gpio_reg_t*) (0x50000300);

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  // Implement me
  // This function should configure the pin as an input/output
  // Hint: Use proper PIN_CNF instead of DIR
  if (gpio_num < 32) {
    if (dir == 0){
    port_zero ->PIN_CNF[gpio_num] = 0;
    }
    else if (dir == 1){
    port_zero ->PIN_CNF[gpio_num] = 3;
    }
  }        
  else {
    if (dir == 0){
      port_one ->PIN_CNF[gpio_num-32] =0;
    }
    else if (dir == 1){
      port_one ->PIN_CNF[gpio_num-32] = 3;
    }
  }
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_set(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin high
  // It can assume that the pin has already been configured
  if (gpio_num < 32) {
        port_zero->OUT |= (1 << gpio_num);
  } else {
   port_one->OUT |= (1 << (gpio_num - 32));
  }
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_clear(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin low
  // It can assume that the pin has already been configured
  if (gpio_num < 32) {
    port_zero->OUT &= ~(1 << gpio_num);
  } else {
    port_one->OUT &= ~(1 << (gpio_num - 32));
  }
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
// Output:
//  bool - pin state (true == high)
bool gpio_read(uint8_t gpio_num) {
  // Implement me
  // This function should read the value from the pin
  // It can assume that the pin has already been configured
  if (gpio_num < 32) {
   return (port_zero->IN >> gpio_num) & 1;
  } else {
    return (port_one->IN >> gpio_num) & 1;
  }
}

// prints out some information about the GPIO driver. Can be called from main()
void gpio_print(void) {
  // Use this function for debugging purposes
  // For example, you could print out struct field addresses
  // You don't otherwise have to write anything here

  printf("Address of PORT0: OUT is %p\n", &(port_zero->OUT));
  printf("Address of PORT0: OUTCLR is %p\n", &(port_zero->OUTCLR));
  printf("Address of PORT0: DIRSET is %p\n", &(port_zero->DIRSET));
  printf("Address of PORT0: DETECTMODE is %p\n", &(port_zero->DETECTMODE));
  printf("Address of PORT0: PIN_CRF[0] is %p\n", &(port_zero->PIN_CNF[0]));

  printf("Address of PORT1: OUT is %p\n", &(port_one->OUT));
  printf("Address of PORT1: OUTCLR is %p\n", &(port_one->OUTCLR));
  printf("Address of PORT1: DIRSET is %p\n", &(port_one->DIRSET));
  printf("Address of PORT1: DETECTMODE is %p\n", &(port_one->DETECTMODE));
  printf("Address of PORT1: PIN_CRF[0] is %p\n", &(port_one->PIN_CNF[0]));
}
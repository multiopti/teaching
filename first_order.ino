#include <SimpleModbusSlave.h>


float Y = 5000;
float U = 2500;

//////////////// registers of your slave ///////////////////
enum 
{     
  // just add or remove registers and your good to go...
  // The first register starts at address 0
  AI0, //0    
  AI1, //1
  AI2, //2
  AI3, //3
  AI4, //4
  AW0, //5    
  AW1, //6
  AW2, //7
  AW3, //8
  AW4, //9
  DI0, //10     
  DI1, //11
  DI2, //12
  DI3, //13
  DI4, //14
  DW0, //15     
  DW1, //16
  DW2, //17
  DW3, //18
  DW4, //19
  TOTAL_ERRORS, //20       
  HOLDING_REGS_SIZE // leave this one
  // total number of registers for function 3 and 16 share the same register array
  // i.e. the same address space
};


unsigned int holdingRegs[HOLDING_REGS_SIZE]; // function 3 and 16 register array
unsigned int counter;
////////////////////////////////////////////////////////////

//void(* resetFunc) (void) = 0;

void setup()
{
 
  modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs);
 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  holdingRegs[AI0] = 5000;
  holdingRegs[AW0] = 2500;
  delay(100);
}

void loop()
{
  
  U = holdingRegs[AW0];
  Y = 0.9672*Y + 0.06557*U;
  
  holdingRegs[AI0] = (unsigned int) Y; // update data to be read by the master
  holdingRegs[AI1] = U; // update data to be read by the master
  holdingRegs[AI2] = 2; // update data to be read by the master
  holdingRegs[AI3] = 3; // update data to be read by the master
  holdingRegs[AI4] = 4; // update data to be read by the master

  holdingRegs[DI0] = 0; // update data to be read by the master
  holdingRegs[DI1] = 0; // update data to be read by the master
  holdingRegs[DI2] = 0; // update data to be read by the master
  holdingRegs[DI3] = 0; // update data to be read by the master
  holdingRegs[DI4] = 0; // update data to be read by the master

  if (holdingRegs[DW0] == 0){
    digitalWrite(LED_BUILTIN, LOW);
    holdingRegs[DI1] = 0;
  }  
  else {
    digitalWrite(LED_BUILTIN, HIGH);
    holdingRegs[DI1] = 1;
  }

holdingRegs[TOTAL_ERRORS] = modbus_update(); 
  
//  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);

 // resetFunc();
  
  
  
}

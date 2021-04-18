#include <SimpleModbusSlave.h>
//////////////// Slave Registers ///////////////////
enum 
{     
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
  HOLDING_REGS_SIZE //21 leave this one
};


unsigned int Registers[HOLDING_REGS_SIZE];
unsigned int counter;

float Y = 500;
float U = 250;

void setup()
{ 
  modbus_configure(&Serial,9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, Registers);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Registers[AI0] = 0;
  delay(10);
}

void loop()
{
  
  // update data to be read by the master
  if (Registers[AI0] < 100){
    Registers[AI0] = Registers[AI0] + 1;
  }  
  else {
    Registers[AI0] = 0;
  }
  Registers[AI1] = 75; // update data to be read by the master
  Registers[AI2] = 100; // update data to be read by the master
  U = Registers[AW0];
  Y = 0.9672*Y + 0.06557*U;
  Registers[AI3] = (unsigned int) Y; // update data to be read by the master
  Registers[AI4] = 5; // update data to be read by the master

  Registers[DI0] = 1; // update data to be read by the master
  Registers[DI2] = 0; // update data to be read by the master
  Registers[DI3] = 1; // update data to be read by the master
  Registers[DI4] = 0; // update data to be read by the master

  if (Registers[DW0] == 0){
    digitalWrite(LED_BUILTIN, LOW);
      Registers[DI1] = 0;
  }  
  else {
    digitalWrite(LED_BUILTIN, HIGH);
      Registers[DI1] = 1;
  }
  
  // modbus_update() is the only method used in loop(). It returns the total error
  // count since the slave started.

  Registers[TOTAL_ERRORS] = modbus_update(); 
  delay(100);
}

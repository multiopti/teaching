#include <SimpleModbusSlave.h>

/* 
   SimpleModbusSlaveV10 supports function 3, 6 & 16.
   
  
   Note:  
   The Arduino serial ring buffer is 64 bytes or 32 registers.
   Most of the time you will connect the arduino to a master via serial
   using a MAX485 or similar.
 
   In a function 3 request the master will attempt to read from your
   slave and since 5 bytes is already used for ID, FUNCTION, NO OF BYTES
   and two BYTES CRC the master can only request 58 bytes or 29 registers.
 
   In a function 16 request the master will attempt to write to your 
   slave and since a 9 bytes is already used for ID, FUNCTION, ADDRESS, 
   NO OF REGISTERS, NO OF BYTES and two BYTES CRC the master can only write
   54 bytes or 27 registers.
 
   Using a USB to Serial converter the maximum bytes you can send is 
   limited to its internal buffer which differs between manufactures. 
*/



// Using the enum instruction allows for an easy method for adding and 
// removing registers. Doing it this way saves you #defining the size 
// of your slaves register array each time you want to add more registers
// and at a glimpse informs you of your slaves register layout.

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
  /* parameters(HardwareSerial* SerialPort,
                long baudrate, 
		unsigned char byteFormat,
                unsigned char ID, 
                unsigned char transmit enable pin, 
                unsigned int holding registers size,
                unsigned int* holding register array)
  */
  
  /* Valid modbus byte formats are:
     SERIAL_8N2: 1 start bit, 8 data bits, 2 stop bits
     SERIAL_8E1: 1 start bit, 8 data bits, 1 Even parity bit, 1 stop bit
     SERIAL_8O1: 1 start bit, 8 data bits, 1 Odd parity bit, 1 stop bit
     
     You can obviously use SERIAL_8N1 but this does not adhere to the
     Modbus specifications. That said, I have tested the SERIAL_8N1 option 
     on various commercial masters and slaves that were suppose to adhere
     to this specification and was always able to communicate... Go figure.
     
     These byte formats are already defined in the Arduino global name space. 
  */
	
  modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs);

  // modbus_update_comms(baud, byteFormat, id) is not needed but allows for easy update of the
  // port variables and slave id dynamically in any function.
  // modbus_update_comms(9600, SERIAL_8N1, 1);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  holdingRegs[AI0] = 0;
  delay(100);
}

void loop()
{
  
  // modbus_update() is the only method used in loop(). It returns the total error
  // count since the slave started. You don't have to use it but it's useful
  // for fault finding by the modbus master.
  holdingRegs[AI0] = holdingRegs[AI0] + 1; // update data to be read by the master
  holdingRegs[AI1] = 1; // update data to be read by the master
  holdingRegs[AI2] = 2; // update data to be read by the master
  holdingRegs[AI3] = 3; // update data to be read by the master
  holdingRegs[AI4] = 4; // update data to be read by the master

  holdingRegs[DI0] = holdingRegs[AI0]; // update data to be read by the master
  holdingRegs[DI1] = 0; // update data to be read by the master
  holdingRegs[DI2] = 0; // update data to be read by the master
  holdingRegs[DI3] = 0; // update data to be read by the master
  holdingRegs[DI4] = 1; // update data to be read by the master

  if (holdingRegs[DW0] == 0){
    digitalWrite(LED_BUILTIN, LOW);
    holdingRegs[DI1] = 0;
  }  
  else {
    digitalWrite(LED_BUILTIN, HIGH);
    holdingRegs[DI1] = 1;
  }

//  holdingRegs[TOTAL_ERRORS] = 1; 
//  counter = 0;
//  while ((holdingRegs[TOTAL_ERRORS] > 0)&&(counter <= 10)) {
//    holdingRegs[TOTAL_ERRORS] = modbus_update(); 
//    counter = counter + 1;
//    delay(10);
//  }
holdingRegs[TOTAL_ERRORS] = modbus_update(); 
  
//  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);

 // resetFunc();
  
  
  
}

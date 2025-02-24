/*	Modbus Serial no Arduino - Exemplo 2
 * 	Por Celso D. A. Ubaldo (celsoautomacao.com.br)
 * 
 * 	@license MIT
 * */

#include <Modbus.h>
#include <ModbusSerial.h>

// Criando objeto do tipo ModbusSerial
ModbusSerial mb;

// Criando uma "união"
typedef union {
  float fvalue;
  word reg[2];
} mbFloat;

void setup() {
  // Habilitando o LED do Arduino como saída
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Configurando os parâmetros seriais Modbus
  mb.config(&Serial, 9600, SERIAL_8N1);
  mb.setSlaveId(1);

  // Adicionando uma bobina (binário)
  mb.addCoil(0, false);
  mb.addCoil(1, true);
  mb.addCoil(2, true);
  
  // Adicionando status de entrada (binário)
  mb.addIsts(0, true);
  mb.addIsts(1, false);
  
  // Adicionando registradores de entrada (16 bits)
  mb.addIreg(0, 49);  
  
  // Criando uma variável do tipo "mbFloat"
  mbFloat mem1;
  mem1.fvalue = 28.9;
  // Vinculando com o endereço Modbus
  mb.addIreg(1, mem1.reg[0]);
  mb.addIreg(2, mem1.reg[1]);
  
  // Adicionando registradores holding (16 bits)
  mb.addHreg(2, 1234);
  
  // Criando uma variável do tipo "mbFloat"
  mbFloat ao0;
  ao0.fvalue = 16.3;
  // Vinculando com o endereço Modbus
  mb.addHreg(0, ao0.reg[0]); 
  mb.addHreg(1, ao0.reg[1]); 
      
}

void loop() { 
  mb.task();

  // Recuperando valor float da comunicação Modbus		
  word end0 = mb.Hreg(0);
  word end1 = mb.Hreg(1);

  // Salvando informação recuperada numa variável "mbFloat"
  mbFloat infoRec;
  infoRec.reg[0] = end0;
  infoRec.reg[1] = end1;

  // Se o valor for maior que 22.0, acende o led do Arduino
  if (infoRec.fvalue > 22.0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

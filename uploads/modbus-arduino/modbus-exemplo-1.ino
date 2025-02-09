/*	Modbus Serial no Arduino - Exemplo 1
 * 	Por Celso D. A. Ubaldo (celsoautomacao.com.br)
 * 
 * 	@license MIT
 * */
 
#include <Modbus.h>
#include <ModbusSerial.h>

// Criando objeto do tipo ModbusSerial
ModbusSerial mb;

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
  
  // Adicionando registrador de entrada (16 bits)
  mb.addIreg(0, 49);  
  
  // Adicionando registrador holding (16 bits)
  mb.addHreg(2, 1234);  
}

void loop() { 
  mb.task();

  // Salvando o estado do endereço 0 (coil) numa variável
  bool estado_led = mb.Coil(0);
  // Associando o estado do LED à variável criada
  digitalWrite(LED_BUILTIN, estado_led);

  
  // Outras funções para ler e alterar valores Modbus:
  /*
   * mb.Ists(0); 		// Apenas ler valor
   * mb.Ists(0, true); 	// Escrever novo valor
   * 
   * mb.Ireg(0); 		// Apenas ler valor
   * mb.Ireg(0, 1234); 	// Escrever novo valor
   * 
   * mb.Hreg(0); 		// Apenas ler valor
   * mb.Hreg(0, 1234); 	// Escrever novo valor   
   * 
   */
  
}

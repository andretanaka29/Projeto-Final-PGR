/*
  UDPSendReceive

  This sketch receives UDP message strings, prints them to the serial port
  and sends an "acknowledge" string back to the sender

  A Processing sketch is included at the end of file that can be used to send
  and received messages for testing with a computer.

  created 21 Aug 2010
  by Michael Margolis

  This code is in the public domain.

*/


#include <SPI.h>          // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>  // UDP library from: bjoern@cs.stanford.edu 12/30/2008


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 177);

unsigned int localPort = 8888;              // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  //buffer to hold incoming packet,

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

int sensorJanela1 = 7;  //sensor para saber se a janela está fechada.
int sensorJanela2 = 6;  //sensor para saber se a janela está totalmente aberta.
int sensorChuva = 5;
int sentidoMotor = 2;  //flag de sentido do motor.
int acionaMotor = 8;

void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);

  Serial.begin(9600);

  pinMode(sensorJanela1, INPUT);
  pinMode(sensorJanela2, INPUT);
  pinMode(sensorChuva, INPUT);
  pinMode(sentidoMotor, OUTPUT);
  pinMode(acionaMotor, OUTPUT);
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  char sensores, dado;

  //bit 2 e bit 6 são sempre em 1 para que o caracter fique em uma faixa sem caracteres especiais.
  bitSet(sensores, 2);
  bitSet(sensores, 6);   

  if (digitalRead(sensorJanela1))
  {
    bitSet(sensores, 0);
  }
  else
  {
    bitClear(sensores, 0);
  }

  if (digitalRead(sensorChuva))
  {
    bitSet(sensores, 4);
  }
  else
  {
    bitClear(sensores, 4);
  }
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i = 0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    dado = packetBuffer;

    //send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(sensores);
    Udp.endPacket();
    Serial.println(sensores);
  }

  Serial.println(packetBuffer);
  if ((packetBuffer == 'a') && digitalRead(sensorJanela2))
  {
    digitalWrite(sentidoMotor, LOW);
    digitalWrite(acionaMotor, HIGH);
  }

  if ((packetBuffer == 'f') && !(digitalRead(sensorJanela1)))
  {
    digitalWrite(sentidoMotor, HIGH);
    digitalWrite(acionaMotor, LOW);   //no módulo de ponte H com a flag de inversão acionada a lógica é invertida.
  }
  else
  {
    digitalWrite(sentidoMotor, LOW);
    digitalWrite(acionaMotor, LOW);
  }

  //chovendo e com a janela aberta é dado o comando para fechar a janela.
  if(!(digitalRead(sensorJanela1)) && digitalRead(sensorChuva))
  {
    digitalWrite(sentidoMotor, HIGH);
    digitalWrite(acionaMotor, LOW);   //no módulo de ponte H com a flag de inversão acionada a lógica é invertida.
  }

  //condições de janela fechada ou totalmente aberta é preciso parar o motor.
  if((digitalRead(sensorJanela1)) || !(digitalRead(sensorJanela2)))
  {
    digitalWrite(sentidoMotor, LOW);
    digitalWrite(acionaMotor, LOW);
  }
  
  delay(100);
}

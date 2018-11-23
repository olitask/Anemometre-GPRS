#include <LowPower.h>

#include <SoftwareSerial.h>
SoftwareSerial SerialAT(6, 7); // RX, TX

#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_RX_BUFFER 600
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

const char apn[]  = "fournisseurmobile.com";// Your GPRS credentials  orange, free,sfr,bouygue
const char user[] = "";// Leave empty, if missing user or pass
const char pass[] = "";

const char server[] = "IP.DE.MON.SER";  //ip de mon serveur;  Name of the server we want to connect to
const int  port     = 80;
// Path to download (this is the bit after the hostname in the URL)
char resource[32] = "/dossier/w.php?o=1&v=2&t=3";  // le dossier avec le fichier php

const int Uanemo = 0;
const int Ugirouette = 1;
const int alim_capteurs = 9;  //base du NPN pour alimenter anemo
const int rst_sim800L = 8;  // pin pour resetter la sim800L
int vitesse;   //String for the first Paramter vitesse
int orientation;   //String for the second Paramter (e.g. orientation)
int i = 0;
const int numReadings = 5;
int readings[numReadings];
int readings2[numReadings];// the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;
int total2 = 0;// the running total
int vitMoy = 0;
int orienMoy = 0; // the average
enum { Mesure, transmission, veille, relance} phaseDeTravail;
unsigned long timeout;

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
HttpClient http(client, server, port);

void setup() {
  SerialAT.begin(9600);
  pinMode (Uanemo, INPUT);  // on declare l'entree anemometre
  pinMode (Ugirouette, INPUT);
  pinMode(alim_capteurs, OUTPUT);
  digitalWrite(alim_capteurs, HIGH);
}

void loop() {

  switch (phaseDeTravail) {
    case Mesure:
      i++;
      vitesse = analogRead(Uanemo);
      vitesse = map(vitesse, 0, 1023 , 0, 100);
      orientation = analogRead(Ugirouette);
      orientation = map(orientation, 128, 620, 0, 360);
      total = total - readings[readIndex];
      total2 = total2 - readings2[readIndex];// read from the sensor:
      readings[readIndex] = vitesse ;
      readings2[readIndex] = orientation ;// add the reading to the total:
      total = total + readings[readIndex];
      total2 = total2 + readings2[readIndex];// advance to the next position in the array:
      readIndex = readIndex + 1;

      // if we're at the end of the array...
      if (readIndex >= numReadings) {
        // ...wrap around to the beginning:
        readIndex = 0;
      }

      // calculate the average:
      vitMoy = total / numReadings;
      orienMoy = total2 / numReadings;

      sprintf(resource, "/dossier/w.php?o=%d&v=%d&t=6", orienMoy, vitMoy);
      delay(2000);
      if (i >= 8) {
        phaseDeTravail = transmission;
        i = 0;
      }
      break;

    case transmission:
      digitalWrite(alim_capteurs, LOW);
      SerialAT.println("AT");    //sortie  mise en veille profonde Dummie AT
      delay(100);
      SerialAT.println("AT+CSCLK=0");     // sortie veille
      delay(100);
      SerialAT.println("AT+CFUN=1");
      delay(4000);
      modem.init();
      modem.simUnlock("0000");  //code pin de la sim
      delay(7000);
      if (!modem.waitForNetwork()) {
        delay(5000);
        return;
      }
      if (!modem.gprsConnect(apn, user, pass)) {
        delay(5000);
        return;
      }
      if (!client.connect(server, port)) {
        delay(10000);
        return;
      }

      // Make a HTTP GET request:
      client.print(String("GET ") + resource + " HTTP/1.0\r\n");
      client.print(String("Host: ") + server + "\r\n");
      client.print("Connection: close\r\n\r\n");
      delay(100);
      client.stop();
      modem.gprsDisconnect();
      delay(1000);
      SerialAT.println("AT+CFUN=0");    // mise en veille profonde du
      delay(500);
      SerialAT.println("AT+CSCLK=2");   // module GPRS
      delay(500);
      phaseDeTravail = veille;
      break;

    case veille:
      for (int j = 0; j < 65; j++) {                       // 70 pour 70 fois 8 secondes de veille
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
           //
      }
      phaseDeTravail = relance;
      break;

    case relance:

      delay(50);
      digitalWrite(alim_capteurs, HIGH);// on alimente les capteurs
      phaseDeTravail = Mesure;
      break;
  }

}


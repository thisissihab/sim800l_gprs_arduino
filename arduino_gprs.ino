#include <SoftwareSerial.h>

String apn = "internet";                    //APN
String apn_u = "";                     //APN-Username
String apn_p = "";                     //APN-Password
String url = "http://sihabthetechguy.info/get_method.php";  //URL of Server

SoftwareSerial mySerial(8, 7); // sim800l_TX_pin, sim800l_RX_pin
int counter = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("SIM800 AT CMD Test");
  mySerial.begin(9600);
  delay(5000);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(2000);
  configure_gprs();
}

void loop() {
  counter++;
  String data = String(counter); //write your data here
  send_to_server(data);
  delay(2000);
}
void send_to_server( String data) {
  String sendURL = url+"?val="+data;
  Serial.println(" --- Start GPRS & HTTP --- ");
  send_to_serial("AT+SAPBR=1,1");
  send_to_serial("AT+SAPBR=2,1");
  send_to_serial("AT+HTTPINIT");
  send_to_serial("AT+HTTPPARA=CID,1");
  send_to_serial("AT+HTTPPARA=URL," + sendURL);
  send_to_serial("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
  send_to_serial("AT+HTTPDATA=192,5000");
  send_to_serial(data);
  send_to_serial("AT+HTTPACTION=1");
  send_to_serial("AT+HTTPREAD");
  send_to_serial("AT+HTTPTERM");
  send_to_serial("AT+SAPBR=0,1");
}

void configure_gprs() {
  Serial.println(" --- CONFIG GPRS --- ");
  send_to_serial("AT+SAPBR=3,1,Contype,GPRS");
  send_to_serial("AT+SAPBR=3,1,APN," + apn);
  if (apn_u != "") {
    send_to_serial("AT+SAPBR=3,1,USER," + apn_u);
  }
  if (apn_p != "") {
    send_to_serial("AT+SAPBR=3,1,PWD," + apn_p);
  }
}

void send_to_serial(String command) {
  Serial.println("Send ->: " + command);
  mySerial.println(command);
  long wtimer = millis();
  while (wtimer + 3000 > millis()) {
    while (mySerial.available()) {
      Serial.write(mySerial.read());
    }
  }
  Serial.println();
}

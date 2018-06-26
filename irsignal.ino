#define MAX_LEN 256

int seq[MAX_LEN], slen = 0, cnt = 0;
int irPin = 11s, val = HIGH;
int ledPin = 13, strobe = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(irPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("Start!");
}

void loop() {
  int val2 = digitalRead(irPin);

  if(val2 == val) {
    cnt++;
    // Following line is a dummy to make if and else sections
    // take about the same time
    if(slen < MAX_LEN) seq[0] = cnt;
    if(cnt > 30000) {
      if(slen) {
        Serial.print("int onoff[");
        Serial.print(slen-1);
        Serial.println("] = {");
        for(int i=1; i<slen; i++) {
          Serial.print(seq[i]);
          if(i+1 < slen) Serial.print(", ");
          if(i%10 == 0) Serial.println();
        }
        Serial.println("n};");
      }
      cnt = 0;
      slen = 0;
    }
  } else { // transition
    if(slen < MAX_LEN) seq[slen++] = cnt; // store if space left
    val = val2;
    cnt = 1;
  }
  delayMicroseconds(5); // results in around 20 us per loop
  digitalWrite(ledPin, strobe); // strobe a LED
  strobe = (strobe == LOW) ? HIGH : LOW; // toggle
}

/*Written By: Er. Dapinder Singh Virk
  Email ID: brillosolutions@gmail.com
  Version: 1.0.1
  Date: October 20, 2018
  Outputs: Scan and break codes on serial terminal.*/

#define clkLine 3
#define dataLine 4
uint8_t kbdBits[33], i = 0;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(clkLine, INPUT);
  pinMode(dataLine, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(clkLine), kbdInterrupt, FALLING);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (i == 33)
  {
    i = 0;
    Serial.print("BIN: ");
    for (int j = 0; j <= 32; j++)
      Serial.print(kbdBits[j]);
    Serial.print("\nHEX: ");
    uint8_t kbdByte = 0, uprLimit = 8, lwrLimit = 1;
    for (int j = 0; j <= 2; j++)
    {
      for (int k = uprLimit; k >= lwrLimit; k--)
        if (kbdBits[k])
        {
          kbdByte <<= 1;
          kbdByte |= 0x01;
        }
        else
          kbdByte <<= 1;
      Serial.print(kbdByte, HEX);
      uprLimit += 11;
      lwrLimit += 11;
    }
    Serial.print("\r\n\n");
  }
}

void kbdInterrupt()
{
  kbdBits[i++] = digitalRead(dataLine);
}

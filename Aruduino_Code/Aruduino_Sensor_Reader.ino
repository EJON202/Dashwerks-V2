
String nom = "Arduino";


int oilPressureInput = A0;    // select the input pin for each sensor
int fuelPressureInput = A1;    
int hallEffectInput = A2;    
int coolantTempInput = A3; 
int pyrometer1Input = A4;
int fiveVoltSupplyVoltage = A5;

int oilPressureReading = 0;  // initalize variables to hold readings
int fuelPressureReading = 0;
int hallEffectReading = 0;
int coolantTempReading = 0;
int pyrometer1Reading = 0;
int fiveVoltSupplyReading = 0;

float oilPressureVoltage = 0; // initalize floats to hold caluclated voltages
float fuelPressureVoltage = 0;
float calculatedRPM = 0;
float coolantTempVoltage = 0;
float pyrometer1Voltage = 0;
float supplyMeasuredVoltage = 0;
               // Hall sensor at pin 2

volatile byte counter;
unsigned int rpm;
unsigned long passedtime;

void isr() ////////////////////////////If trouble with Tach, look here and at hall effect logic blocks//////////<<<<<<----------

 {
   //Each rotation, this interrupt function is run twice, so take that into consideration for , calculating RPM,
   //Update count

      counter++;
 }

void setup() {
  Serial.begin(9600);  // open serial comms

  attachInterrupt(0, isr, RISING); //Interrupts are called on Rise of Input //////////////   <<<<<<------------------
  pinMode(hallEffectInput, INPUT); //Sets hallsensor as input
  counter = 0;
  rpm = 0;
  passedtime = 0; //Initialise the values                                   /////   <<<<<---------

}

void loop() {

//////////////////////////////////////////////HallEffect to RPM Logic/////////////////////////   <<<<<----------------

   detachInterrupt(0); //Interrupts are disabled

   rpm = 60*500/(millis() - passedtime)*counter;

   passedtime = millis();

   counter = 0;

   Serial.print("RPM=");
   Serial.println(rpm); //Print out result to monitor

   attachInterrupt(0, isr, RISING);   //Restart the interrupt processing

//////////////////////////////////////////System Reading Input and conversion to voltages/////////////////////////////////
 
  oilPressureReading = analogRead(oilPressureInput);  //check readings and store in variables
  fuelPressureReading = analogRead(fuelPressureInput);
  coolantTempReading = analogRead(coolantTempInput);
  pyrometer1Reading = analogRead(pyrometer1Input);
  fiveVoltSupplyReading = analogRead(fiveVoltSupplyVoltage);

  oilPressureVoltage = oilPressureReading * (5.0/ 1023.0); //calculate voltages from inital readings and store
  fuelPressureVoltage = fuelPressureReading * (5.0/ 1023.0);
  coolantTempVoltage = coolantTempReading * (5.0/ 1023.0);
  pyrometer1Voltage = pyrometer1Reading * (5.0/ 1023.0);
  fiveVoltSupplyVoltage = fiveVoltSupplyReading * (5.0/ 1023.0);
  
  /////////////////////////////////////System Report to Serial///////////////////////////////////////

  Serial.print("OilPressure Voltage ");
  Serial.println(oilPressureVoltage);
  Serial.print("FuelPressure Voltage ");
  Serial.println(fuelPressureVoltage);

  Serial.print("CoolantTemp Voltage: ");
  Serial.println(coolantTempVoltage);
  Serial.print("Pyrometer 1 Reading Voltage: ");
  Serial.println(pyrometer1Voltage);
  Serial.print("System 5v Supply Actual V: ");
  Serial.println(fiveVoltSupplyVoltage);

  oilPressureVoltageString = str(oilPressureVoltage)
  
  Serial.println(oilPressureVoltageString);
  
  Serial.println();
  delay(500);

}

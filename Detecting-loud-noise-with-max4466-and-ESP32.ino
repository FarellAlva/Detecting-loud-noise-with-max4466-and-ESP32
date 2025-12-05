#define MIC_PIN 34
#define LED_BUILTIN 2
#define LED_EXT 13
#define SAMPLE_WINDOW 50 

int threshold = 1500; 

void setup() {
  Serial.begin(115200);
  
  pinMode(MIC_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_EXT, OUTPUT);
  
  analogSetAttenuation(ADC_11db); 
}

void loop() {
  unsigned long startMillis = millis(); 
  unsigned int signalMax = 0;
  unsigned int signalMin = 4095;
  
  // Sampling process
  while (millis() - startMillis < SAMPLE_WINDOW)
  {
     int sample = analogRead(MIC_PIN);
     
     if (sample < 4095) 
     {
        if (sample > signalMax) signalMax = sample;
        else if (sample < signalMin) signalMin = sample;
     }
  }
  
  int peakToPeak = signalMax - signalMin; 
  
  if (peakToPeak > threshold) {
     digitalWrite(LED_BUILTIN, HIGH);
     digitalWrite(LED_EXT, HIGH);
  } else {
     digitalWrite(LED_BUILTIN, LOW);
     digitalWrite(LED_EXT, LOW);
  }
  Serial.print("Volume:"); Serial.print(peakToPeak);
  Serial.print(",Threshold:"); Serial.println(threshold);
}

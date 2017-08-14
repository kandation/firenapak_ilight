#define MicSamples (1024*2)
#define MicPin A0
void MeasureAnalog()
{
    long signalAvg = 0, signalMax = 0, signalMin = 1024, t0 = millis();
    for (int i = 0; i < MicSamples; i++)
    {
        int k = analogRead(MicPin);
        signalMin = min(signalMin, k);
        signalMax = max(signalMax, k);
        signalAvg += k;
    }
    signalAvg /= MicSamples;
 
    // print
    /*Serial.print("Time: " + String(millis() - t0));
    Serial.print(" Min: " + String(signalMin));
    Serial.print(" Max: " + String(signalMax));
    Serial.print(" Avg: " + String(signalAvg));
    Serial.print(" Span: " + String(signalMax - signalMin));
    Serial.print(", " + String(signalMax - signalAvg));
    Serial.print(", " + String(signalAvg - signalMin));
    Serial.println("");
    */
    //Serial.print(millis() - t0);
    Serial.print(signalMin);
    Serial.print(signalMax);
    Serial.print(signalAvg);
    Serial.print(signalMax - signalMin);
    Serial.print(signalMax - signalAvg);
    Serial.print(signalAvg - signalMin);
    Serial.println("");
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A0, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //MeasureAnalog();
  Serial.println(analogRead(A0));
  delay(33);
  

}

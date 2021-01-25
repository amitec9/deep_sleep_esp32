/*
Deep Sleep multiple with timer Wake Up
*/
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10  
#define TIME_TO_SLEEP1  30  
RTC_DATA_ATTR int bootCount = 1;

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/


void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

 
void fun_timer()
{
  if(bootCount%4==0){
  Serial.println("fun_timer");
  Serial.println("Going to sleep now");
  Serial.flush(); 
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
  }
}
void fun_timer1()
{
  Serial.println("fun_timer1");
  Serial.println("Going to sleep now");
  Serial.flush(); 
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP1 * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}
void setup(){
  Serial.begin(9600);
  delay(1000); //Take some time to open up the Serial Monitor
  ++bootCount;
  fun_timer();
  fun_timer1();
}

void loop(){
  //This is not going to be called
}
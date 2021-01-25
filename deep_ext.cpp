/*
Deep Sleep with External Wake Up
*/
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10  

RTC_DATA_ATTR int bootCount = 1;

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/

int button = 12;
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
void fun_ext()
{

  /*
  First we configure the wake up source
  We set our ESP32 to wake up for an external trigger.
  There are two types for ESP32, ext0 and ext1 .
  ext0 uses RTC_IO to wakeup thus requires RTC peripherals
  to be on while ext1 uses RTC Controller so doesnt need
  peripherals to be powered on.
  Note that using internal pullups/pulldowns also requires
  RTC peripherals to be turned on.
  */
 
  Serial.println("rtc");
  if (digitalRead(button) == HIGH) {
    print_wakeup_reason();
  delay(30000);
   esp_sleep_enable_ext0_wakeup(GPIO_NUM_12,1); //1 = High, 0 = Low//GPIO_NUM_13
   esp_deep_sleep_start();
   Serial.println("This will never be printed");
}
}
void fun_timer()
{
  Serial.println("fun_timer");
  Serial.println("Going to sleep now");
  delay(60000);
  Serial.flush(); 
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}
void setup(){
  Serial.begin(9600);
  delay(1000); //Take some time to open up the Serial Monitor
  pinMode(button, INPUT);
  fun_ext();
  fun_timer();
}

void loop(){
  //This is not going to be called
}
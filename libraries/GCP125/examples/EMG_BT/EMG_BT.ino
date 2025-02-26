//-------------------------------------------------------------------//
// Warning：
// SysTick_Handler() and SysTick_Config() should exist at the same time
// or your compiled device would encounter fatal error and dead.
//---------------------------------------------------------------------//
#include <bluefruit.h>
#define BUF_LENGTH          108
#define DEVICE_NAME       "Alano BLE"
#define TICK_INTERVAL_us    2000 //official Sample rate -> set this to 1000 
static uint8_t adc_value_ch1[BUF_LENGTH] = {0,};
static uint8_t counter = 0;
static bool connected2 = false;
BLEDis  bledis;    // DIS (Device Information Service) helper class instance

#define CUSTOM_UUID_SERVICE     0xA000
#define CHANNEL1_UUID_CHR_RAW   0xA001
BLEService        custom(CUSTOM_UUID_SERVICE);
BLECharacteristic ch1(CHANNEL1_UUID_CHR_RAW);

uint8_t FlashCount;
static bool FlashOnOff = 0;

#define _PINNUM(port, pin)    ((port)*32 + (pin))
#define LED_1                 _PINNUM(0, 13)	//Red
#define LED_2                 _PINNUM(0, 14)	//Green
#define LED_3                 _PINNUM(0, 15)	//Blue
#define LED_4                 _PINNUM(0, 16)	//Yellow

#define KEY_1                 _PINNUM(0, 11)
#define KEY_2                 _PINNUM(0, 12)
#define KEY_3                 _PINNUM(0, 24)
#define KEY_4                 _PINNUM(0, 25)

#define LO_N                 _PINNUM(0, 26)
#define LO_P                 _PINNUM(0, 27)
#define SDN_CTL              _PINNUM(1, 8)

extern "C"
{
  volatile uint32_t last_pulse_time = 0; // 上次脉冲时间
  const uint32_t pulse_duration_ms = 200; // LED 点亮时长，单位ms
  const uint8_t ecgH_threshold = 135; // 假设 ECG 信号阈值
  const uint8_t ecgL_threshold = 105; // 假设 ECG 信号阈值

  void SysTick_Handler(void)
  {
    if (connected2) {
      uint8_t ecg_signal = analogRead(A0);
      adc_value_ch1[counter] = ecg_signal;+
      counter++;
      adc_value_ch1[counter] = analogRead(A3);
      counter++;
      adc_value_ch1[counter] = analogRead(A2);
      counter++;
      Serial.println(ecg_signal);
      if (((ecg_signal > ecgH_threshold) || (ecg_signal < ecgL_threshold))  && (millis() - last_pulse_time > pulse_duration_ms))
      {
        digitalWrite(PIN_NEOPIXEL, LOW); // 点亮 LED
        last_pulse_time = millis();     // 记录当前时间
      }

      // 自动熄灭 LED
      if (millis() - last_pulse_time >= pulse_duration_ms)
      {
        digitalWrite(PIN_NEOPIXEL, HIGH); // 关闭 LED
      }

      if (counter >= BUF_LENGTH) {
        ch1.notify(adc_value_ch1, BUF_LENGTH);
        counter = 0;
      }
      
      digitalWrite(LED_2, LOW); // 点亮 LED
    }
   	else
    {
    	FlashCount++;
    	if(FlashCount==0)
    	{
    		if(FlashOnOff==0)
    		{
    			FlashOnOff = 1;
    			digitalWrite(LED_2, LOW); // 点亮 LED
    		}
    		else
    		{
    			FlashOnOff = 0;
    			digitalWrite(LED_2, HIGH); // 关闭 LED
    		}
    	}
    }
  }
} // extern C

void setup()
{
	unsigned char Tmpi;
  //设置所有的IO为输出0
  for(Tmpi=0;Tmpi<48;Tmpi++)
  {
    pinMode(Tmpi, OUTPUT);
    digitalWrite(Tmpi, LOW);
  }
  //按键定义为输入上拉
  pinMode(KEY_1, INPUT_PULLUP);
  pinMode(KEY_2, INPUT_PULLUP);
  pinMode(KEY_3, INPUT_PULLUP);
  pinMode(KEY_4, INPUT_PULLUP);
  pinMode(LO_N, INPUT);
  pinMode(LO_P, INPUT);
  pinMode(SDN_CTL, OUTPUT);

  digitalWrite(SDN_CTL, HIGH);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, HIGH);
  digitalWrite(LED_4, HIGH);
  
  //analogReference(AR_DEFAULT);
  analogReference(AR_INTERNAL_3_0);  
  //analogReadResolution(10);
  analogReadResolution(8);
	
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_NEOPIXEL, OUTPUT); // 配置为输出引脚
  digitalWrite(PIN_NEOPIXEL, LOW); // 初始化为关闭状态
  Serial.begin(115200);
  bleSetup();
  SysTick_Config((F_CPU / 1000000) * TICK_INTERVAL_us);
}


void bleSetup(void) {
  Serial.println("Bluefruit52 nRF Blinky Example");
  Serial.println("------------------------------\n");
  analogReadResolution(8);

  Serial.println("Initialise the Bluefruit nRF52 module");
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
  Bluefruit.begin();
  Bluefruit.setName(DEVICE_NAME);
  Bluefruit.setTxPower(4);

  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);
  Bluefruit.Periph.setConnInterval(16, 32);

  Serial.println("Configuring the Device Information Service");
  bledis.setManufacturer("Yutech, Taiwan");
  bledis.setModel("TriAnswer");
  bledis.begin();

  custom.begin();
  ch1.setProperties(CHR_PROPS_READ | CHR_PROPS_NOTIFY);
  ch1.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  ch1.setMaxLen(BUF_LENGTH);
  ch1.setFixedLen(BUF_LENGTH);
  ch1.begin();
  startAdv();

}
void startAdv(void)
{
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  //Bluefruit.Advertising.addService(custom);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

void loop()
{

}

void connect_callback(uint16_t conn_handle)
{
  BLEConnection* conn = Bluefruit.Connection(conn_handle);
  Serial.println("Request to change MTU");
  conn->requestMtuExchange(123);
  Serial.println("Connected");
  delay(1000);
  connected2 = true;
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
  connected2 = false;
}

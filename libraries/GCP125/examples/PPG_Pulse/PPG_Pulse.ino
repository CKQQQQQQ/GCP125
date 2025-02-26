

#define SAMPLE_RATE 	125
#define BAUD_RATE 		115200
#define INPUT_PIN 		A0
#define LED_PIN 		  PIN_LED3

void setup() {
  // Serial connection begin
  Serial.begin(BAUD_RATE);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // 初始化为关闭状态
}

void loop() {
  volatile uint32_t last_pulse_time = 0; // 上次脉冲时间
  const uint32_t pulse_duration_ms = 200; // LED 点亮时长，单位ms
  const int ecg_threshold = 380; // 假设 ECG 信号阈值
  
  // Calculate elapsed time
  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;
  past = present;

  // Run timer
  static long timer = 0;
  timer -= interval;

  // Sample
  if(timer < 0){
    timer += 1000000 / SAMPLE_RATE;
    float sensor_value = analogRead(INPUT_PIN);
    //float signal = ECGFilter(sensor_value);
    Serial.println(sensor_value);
    
    if (sensor_value > ecg_threshold && (millis() - last_pulse_time > pulse_duration_ms))
      {
        digitalWrite(LED_PIN, LOW); // 点亮 LED
        last_pulse_time = millis();     // 记录当前时间
      }

      // 自动熄灭 LED
      if (millis() - last_pulse_time >= pulse_duration_ms)
      {
        digitalWrite(LED_PIN, HIGH); // 关闭 LED
      }
  }
}

// Band-Pass Butterworth IIR digital filter, generated using filter_gen.py.
// Sampling rate: 125.0 Hz, frequency: [0.5, 44.5] Hz.
// Filter is order 4, implemented as second-order sections (biquads).
// Reference:
// https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
// https://courses.ideate.cmu.edu/16-223/f2020/Arduino/FilterDemos/filter_gen.py
float ECGFilter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - 0.70682283*z1 - 0.15621030*z2;
    output = 0.28064917*x + 0.56129834*z1 + 0.28064917*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - 0.95028224*z1 - 0.54073140*z2;
    output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.95360385*z1 - 0.95423412*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.98048558*z1 - 0.98111344*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}

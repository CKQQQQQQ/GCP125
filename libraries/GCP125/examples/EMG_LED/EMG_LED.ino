

#define SAMPLE_RATE 	125
#define BAUD_RATE 		115200
#define INPUT_PIN 		A0

#define _PINNUM(port, pin)    ((port)*32 + (pin))
#define LED_PIN				_PINNUM(0, 15)

void setup() {
  // Serial connection begin
  Serial.begin(BAUD_RATE);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // 初始化为关闭状态
}

void loop() {
  volatile uint32_t last_pulse_time = 0; // 上次脉冲时间
  const uint32_t pulse_duration_ms = 200; // LED 点亮时长，单位ms
  const int ecgH_threshold = 400; // 假设 ECG 信号阈值
  const int ecgL_threshold = 300; // 假设 ECG 信号阈值
  
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
    //float signal = EMGFilter(sensor_value);
    Serial.println(sensor_value);
    
    if (((sensor_value > ecgH_threshold) || (sensor_value < ecgL_threshold))  && (millis() - last_pulse_time > pulse_duration_ms))
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
// Sampling rate: 500.0 Hz, frequency: [74.5, 149.5] Hz.
// Filter is order 4, implemented as second-order sections (biquads).
// Reference: 
// https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
// https://courses.ideate.cmu.edu/16-223/f2020/Arduino/FilterDemos/filter_gen.py
float EMGFilter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - 0.05159732*z1 - 0.36347401*z2;
    output = 0.01856301*x + 0.03712602*z1 + 0.01856301*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -0.53945795*z1 - 0.39764934*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - 0.47319594*z1 - 0.70744137*z2;
    output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.00211112*z1 - 0.74520226*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}

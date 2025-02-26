

#define SAMPLE_RATE 	75
#define BAUD_RATE 		115200
#define INPUT_PIN 		A0

volatile uint32_t last_pulse_time = 0; // 上次脉冲时间
const uint32_t pulse_duration_ms = 200; // LED 点亮时长，单位ms
#define HIGH_THRESHOLD 400
#define LOW_THRESHOLD  250
#define MIDL_THRESHOLD 300
#define MIDH_THRESHOLD 350  // 中间阈值，用于状态切换
static bool cent_flag = true;
static bool left_flag = false;
static bool right_flag = false;


void setup() {
  // Serial connection begin
  Serial.begin(BAUD_RATE);
  pinMode(PIN_LED1, OUTPUT);
  digitalWrite(PIN_LED1, HIGH); // 初始化为关闭状态
  pinMode(PIN_LED2, OUTPUT);
  digitalWrite(PIN_LED2, HIGH); // 初始化为关闭状态
}

void loop() {
  // Calculate elapsed time
  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;
  past = present;

  // Run timer
  static long timer = 0;
  timer -= interval;

  // Sample
  if (timer < 0) {
    timer += 1000000 / SAMPLE_RATE;
    float sensor_value = analogRead(INPUT_PIN);
    //float signal = EOGFilter(sensor_value);
    Serial.println(sensor_value);

    // 状态机逻辑
    if (!left_flag && cent_flag && !right_flag) {  // 当前状态为010
      if (sensor_value > HIGH_THRESHOLD) {
        // 转换到状态100，LED1点亮
        left_flag = true;
        cent_flag = false;
        right_flag = false;
        digitalWrite(PIN_LED1, LOW); // LED1点亮
        digitalWrite(PIN_LED2, HIGH);  // LED2熄灭
      } else if (sensor_value < LOW_THRESHOLD) {
        // 转换到状态001，LED2点亮
        left_flag = false;
        cent_flag = false;
        right_flag = true;
        digitalWrite(PIN_LED1, HIGH);  // LED1熄灭
        digitalWrite(PIN_LED2, LOW); // LED2点亮
      }
    }
    else if (left_flag && !cent_flag && !right_flag) {  // 当前状态为100
      if (sensor_value < LOW_THRESHOLD) {
        // 转换到状态110，LED1熄灭
        left_flag = true;
        cent_flag = true;
        right_flag = false;
        digitalWrite(PIN_LED1, HIGH);  // LED1熄灭
        digitalWrite(PIN_LED2, HIGH);  // LED2熄灭
      }
    }
    else if (!left_flag && !cent_flag && right_flag) {  // 当前状态为001
      if (sensor_value > HIGH_THRESHOLD) {
        // 转换到状态011，LED2熄灭
        left_flag = false;
        cent_flag = true;
        right_flag = true;
        digitalWrite(PIN_LED1, HIGH);  // LED1熄灭
        digitalWrite(PIN_LED2, HIGH);  // LED2熄灭
      }
    }
    else if (left_flag && cent_flag && !right_flag) {  // 当前状态为110
      if (sensor_value > MIDL_THRESHOLD) {
        // 转换到状态010，LED1和LED2熄灭
        left_flag = false;
        cent_flag = true;
        right_flag = false;
        digitalWrite(PIN_LED1, HIGH);  // LED1熄灭
        digitalWrite(PIN_LED2, HIGH);  // LED2熄灭
      }
    }
    else if (!left_flag && cent_flag && right_flag) {  // 当前状态为011
      if (sensor_value < MIDH_THRESHOLD) {
        // 转换到状态010，LED1和LED2熄灭
        left_flag = false;
        cent_flag = true;
        right_flag = false;
        digitalWrite(PIN_LED1, HIGH);  // LED1熄灭
        digitalWrite(PIN_LED2, HIGH);  // LED2熄灭
      }
    }
  }
}

// Band-Pass Butterworth IIR digital filter, generated using filter_gen.py.
// Sampling rate: 75.0 Hz, frequency: [0.5, 19.5] Hz.
// Filter is order 4, implemented as second-order sections (biquads).
// Reference:
// https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
// https://courses.ideate.cmu.edu/16-223/f2020/Arduino/FilterDemos/filter_gen.py
float EOGFilter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - 0.02977423 * z1 - 0.04296318 * z2;
    output = 0.09797471 * x + 0.19594942 * z1 + 0.09797471 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - 0.08383952 * z1 - 0.46067709 * z2;
    output = 1.00000000 * x + 2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.92167271 * z1 - 0.92347975 * z2;
    output = 1.00000000 * x + -2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.96758891 * z1 - 0.96933514 * z2;
    output = 1.00000000 * x + -2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}

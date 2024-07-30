// Leonardo PIN 3
// Uno / Nano PIN 2
#define DATAPIN 2
#define INTERRUPT 0

#define MAX_CHANGES 256

#define T 740
#define T_GAP T * 6
#define T_START T * 3
#define T_0 T
#define T_1 T * 2
unsigned int timings[MAX_CHANGES];

volatile unsigned int ringIndex = 0;
int tolerance = T / 4;

bool THRESHOLD(int value, unsigned long delay) {
  if (value < delay - tolerance) {
    return false;
  }
  if (value > delay + tolerance) {
    return false;
  }
  return true;
}

bool dump(unsigned int changeCount) {
  for (int i = 0; i < changeCount; i += 2) {
    if (THRESHOLD(timings[i], T_0) && THRESHOLD(timings[i + 1], T_0)) {
      Serial.print("0");
    } else if (THRESHOLD(timings[i], T_1) && THRESHOLD(timings[i + 1], T_0)) {
      Serial.print("1");
    } else {
      Serial.print(" (");
      Serial.print(timings[i]);
      Serial.print(" ");
      Serial.print(timings[i + 2]);
      Serial.print(") ");
    }
  }

  Serial.print("\n");
}

static unsigned int state = 0;
static unsigned int changeCount = 0;
static unsigned long lastTime = 0;

void handleInterrupt() {
  const long time = micros();
  const unsigned int duration = time - lastTime;

  if (duration > T_GAP) {
    state = 1;
  } else if (state == 1 && THRESHOLD(duration, T_START)) {
    state = 2;
    changeCount = 0;
  } else if (state == 2) {
    timings[changeCount++] = duration;
  }

  if (changeCount == 44) {
    dump(changeCount);
    state = 0;
    changeCount = 0;
  }

  if (changeCount >= MAX_CHANGES) {
    state = 0;
  }

  lastTime = time;
}

void setup() {
  Serial.begin(9600);
  attachInterrupt(INTERRUPT, handleInterrupt, CHANGE);
}

void loop() {
}

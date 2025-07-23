// Motor pins
const int in1 = 7, in2 = 6;
const int in3 = 5, in4 = 4;
const int ena = 9, enb = 10;

// IR sensor pins
const int irl = 3;  // Left
const int irc = 8;  // Center
const int irr = 2;  // Right

// PID constants (Tune these experimentally)
float Kp = 25;
float Ki = 0;
float Kd = 15;

int baseSpeed = 120;
int maxSpeed = 255;

float error = 0;
float previousError = 0;
float integral = 0;

void setup() {
  Serial.begin(9600);

  // Motor pins
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT); pinMode(enb, OUTPUT);

  // IR sensors
  pinMode(irl, INPUT);
  pinMode(irc, INPUT);
  pinMode(irr, INPUT);
}

void loop() {
  // Read IR sensors
  int left = digitalRead(irl);   // 0 = black
  int center = digitalRead(irc);
  int right = digitalRead(irr);

  // Compute error using weighted sum
  if (left == 0 && center == 1 && right == 1) {
    error = -1;
  } else if (left == 0 && center == 0 && right == 1) {
    error = -0.5;
  } else if (left == 1 && center == 0 && right == 1) {
    error = 0;
  } else if (left == 1 && center == 0 && right == 0) {
    error = 0.5;
  } else if (left == 1 && center == 1 && right == 0) {
    error = 1;
  } else if (left == 0 && center == 0 && right == 0) {
    error = 0; // perfectly centered
  } else {
    // Lost line — all white
    stopMotors();
    return;
  }

  // PID Calculations
  integral += error;
  float derivative = error - previousError;
  float correction = Kp * error + Ki * integral + Kd * derivative;
  previousError = error;

  // Calculate motor speeds
  int leftSpeed = constrain(baseSpeed - correction, 0, maxSpeed);
  int rightSpeed = constrain(baseSpeed + correction, 0, maxSpeed);

  moveForward(leftSpeed, rightSpeed);

  // Debugging
  Serial.print("L:"); Serial.print(left);
  Serial.print(" C:"); Serial.print(center);
  Serial.print(" R:"); Serial.print(right);
  Serial.print(" | Error: "); Serial.print(error);
  Serial.print(" | Correction: "); Serial.print(correction);
  Serial.print(" | LSpeed: "); Serial.print(leftSpeed);
  Serial.print(" | RSpeed: "); Serial.println(rightSpeed);

  delay(10); // Small delay for loop stability
}

void moveForward(int lSpeed, int rSpeed) {
  // Left motor
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  analogWrite(ena, lSpeed);

  // Right motor
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(enb, rSpeed);
}

void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  analogWrite(ena, 0); analogWrite(enb, 0);
}

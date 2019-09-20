#include <Servo.h>

#define TRIG 10
#define ECHO 11
#define BUZZER 8
#define velocity_right 2
#define right_motor_a 4
#define right_motor_b 3
#define velocity_left 5
#define left_motor_a 6
#define left_motor_b 7


float lenght_of_time;
float distance, distancex;
int pos = 90;
int vel = 250;
int break_time = 500;

Servo myservo;

void setup()
{
  myservo.attach(9);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(velocity_right, OUTPUT);
  pinMode(velocity_left, OUTPUT);
  pinMode(right_motor_a, OUTPUT);
  pinMode(right_motor_b, OUTPUT);
  pinMode(left_motor_a, OUTPUT);
  pinMode(left_motor_b, OUTPUT);

  analogWrite(velocity_right, 0);
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, LOW);

  analogWrite(velocity_left, 0);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, LOW);

  Serial.begin(9600);

}

void going_foward(void) {
  analogWrite(velocity_right, vel);
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, HIGH);

  analogWrite(velocity_left, vel);
  digitalWrite(left_motor_a, HIGH);
  digitalWrite(left_motor_b, LOW);
}

void stop_walking(void) {
  analogWrite(velocity_right, 0);
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, LOW);

  analogWrite(velocity_left, 0);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, LOW);
}

void turn_right(void) {
  stop_walking();
  delay(break_time/5);
  analogWrite(velocity_right, vel);
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, LOW);

  analogWrite(velocity_left, vel);
  digitalWrite(left_motor_a, HIGH);
  digitalWrite(left_motor_b, LOW);
}

void turn_left(void) {
  stop_walking();
  delay(break_time/5);
  analogWrite(velocity_right, vel);
  digitalWrite(right_motor_a, LOW);
  digitalWrite(right_motor_b, HIGH);

  analogWrite(velocity_left, vel);
  digitalWrite(left_motor_a, LOW);
  digitalWrite(left_motor_b, LOW);
}

float save_distance(int delaytime) {
  digitalWrite(TRIG, LOW);
  delay(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  lenght_of_time = pulseIn(ECHO, HIGH);

  distancex = lenght_of_time / 58;

  Serial.print("cm: ");
  Serial.println(distancex);

  delay(delaytime);

  return distancex;

}
float search(int delaytime) {
  digitalWrite(TRIG, LOW);
  delay(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  lenght_of_time = pulseIn(ECHO, HIGH);

  distance = lenght_of_time / 58;

  Serial.print("Distance(cm): ");
  Serial.println(distance);

  delay(delaytime);

  return distance;

}
void look_left()
{
  for (pos = 90; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  while (1) {
    save_distance(0);
    delay(break_time/2);
    break;
  }
  for (pos = 180; pos >= 90; pos -= 1) {
    myservo.write(pos);
  }
}
void look_right()
{
  for (pos = 90; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  while (1) {
    save_distance(0);
    delay(break_time/2);
    break;
  }
  for (pos = 0; pos <= 90; pos += 1) {
    myservo.write(pos);
  }
}

void buzzers_alert2() {
  digitalWrite(BUZZER, HIGH);
  delay(break_time/2);

  digitalWrite(BUZZER, LOW);
  delay(break_time/2);

  digitalWrite(BUZZER, HIGH);
  delay(break_time/2);

  digitalWrite(BUZZER, LOW);
}
void buzzers_alert3() {
  digitalWrite(BUZZER, HIGH);
  delay(break_time/2);

  digitalWrite(BUZZER, LOW);
  delay(break_time/2);

  digitalWrite(BUZZER, HIGH);
  delay(break_time/2);

  digitalWrite(BUZZER, LOW);
  delay(break_time/2);

  digitalWrite(BUZZER, HIGH);
  delay(break_time/2);

  digitalWrite(BUZZER, LOW);
}
void loop()
{
  going_foward();
  search(0);
  if (distance < 40 && distance > 0) {

    stop_walking();

    delay(break_time);

    digitalWrite(BUZZER, HIGH);
    delay(break_time);
    digitalWrite(BUZZER, LOW);

    Serial.println("Stopped");

    look_left();
    if (distancex > 40 || distancex < 0) {
      buzzers_alert2();
      delay(break_time);

      Serial.println("turning left" );
      turn_left();
      delay(break_time/2);

    } else {
      look_right();
      if (distancex > 40 || distancex < 0) {
        buzzers_alert3();
        delay(break_time);

        Serial.println("turning right" );
        turn_right();
        delay(break_time/2);

      } else {
        Serial.println("going back");
        turn_right();
        delay(break_time);
      }
    }
  }
}

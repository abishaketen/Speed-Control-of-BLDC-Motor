#include <Servo.h>

#define TRIG_PIN 9       // Pin for the ultrasonic sensor TRIG
#define ECHO_PIN 10      // Pin for the ultrasonic sensor ECHO
#define ESC_PIN 6        // Pin to control the ESC
#define MAX_DISTANCE 100 // Maximum distance in cm to reduce speed
#define MIN_SPEED 1000   // Minimum PWM pulse width (for motor stop or minimum speed)
#define MAX_SPEED 2000   // Maximum PWM pulse width (for full speed)

// Create a Servo object to control the ESC
Servo esc;

void setup() {
    // Set up the ultrasonic sensor pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Attach ESC to the ESC pin
    esc.attach(ESC_PIN, MIN_SPEED, MAX_SPEED);

    // Begin Serial communication (optional for debugging)
    Serial.begin(9600);
}

void loop() {
    // Measure the distance
    int distance = getDistance();

    // Map distance to a speed value
    int speed = mapDistanceToSpeed(distance);

    // Control the ESC with the speed
    esc.writeMicroseconds(speed);

    // Optional debugging output
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm, Speed: ");
    Serial.println(speed);

    // Delay for stability
    delay(50);
}

// Function to get distance from the ultrasonic sensor
int getDistance() {
    // Clear the TRIG_PIN
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    // Set the TRIG_PIN high for 10 microseconds
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read the duration of the pulse on ECHO_PIN
    long duration = pulseIn(ECHO_PIN, HIGH);

    // Convert duration to distance in cm
    int distance = duration * 0.034 / 2; // Speed of sound = 0.034 cm/us

    return distance;
}

// Function to map distance to speed
int mapDistanceToSpeed(int distance) {
    if (distance > MAX_DISTANCE) {
        // No obstacle within MAX_DISTANCE, set to maximum speed
        return MAX_SPEED;
    } else {
        // Map the distance to a speed in the range MIN_SPEED to MAX_SPEED
        return map(distance, 0, MAX_DISTANCE, MIN_SPEED, MAX_SPEED);
    }
}

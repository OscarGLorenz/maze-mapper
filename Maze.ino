#include "Arduino.h"
#include "MazeObjects.h"

//The setup function is called once at startup of the sketch
Maze maze;

void setup() {
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop() {

	if (Serial.available() > 0) {
		String string = Serial.readString();
		if (string.equalsIgnoreCase("F")) {
			Serial.println("front");
			maze.straight();
		} else if (string.equalsIgnoreCase("L")) {
			Serial.println("left");
			maze.turnLeft();
		} else if (string.equalsIgnoreCase("R")) {
			Serial.println("right");
			maze.turnRight();
		} else if (string.equalsIgnoreCase("B")) {
			Serial.println("back");
			maze.turnBack();
		} else if (string.equalsIgnoreCase("E")) {
			Serial.println("exit");
			maze.finish();
			maze.turnBack();
		} else if (string.equalsIgnoreCase("SOLVE")) {
			Serial.println("solving....");
			ArrayList<Dir> * dirs = maze.solve();
			for (int i = 0; i < dirs->size(); i++) {
				switch (dirs->get(i)) {
				case FRONT:
					Serial.print("F");
					break;
				case LEFT:
					Serial.print("L");
					break;
				case RIGHT:
					Serial.print("R");
					break;
				case BACK:
					Serial.print("B");
					break;
				}
			}
		} else if (string.startsWith("%")) {
			for (unsigned int i = 1; i < string.length(); i++) {
				switch (string.charAt(i)) {
				case 'F':
				case 'f':
					maze.straight();
					break;
				case 'b':
				case 'B':
					maze.turnBack();
					break;
				case 'l':
				case 'L':
					maze.turnLeft();
					break;
				case 'r':
				case 'R':
					maze.turnRight();
					break;
				case 'e':
				case 'E':
					maze.finish();
					break;
			}
		}
	}
}
}

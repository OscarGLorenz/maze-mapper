#include "Arduino.h"
#include "MazeObjects.hpp"

//The setup function is called once at startup of the sketch

void setup() {
	Serial.begin(9600);
}

Iterator itr;

// The loop function is called in an endless loop
void loop() {

	if (Serial.available() > 0) {
		String string = Serial.readString();
		if (string.equalsIgnoreCase("F")) {
			Serial.println("front");
			itr.move(FRONT, NORMAL);
		} else if (string.equalsIgnoreCase("L")) {
			Serial.println("left");
			itr.move(LEFT, NORMAL);
		} else if (string.equalsIgnoreCase("R")) {
			Serial.println("right");
			itr.move(RIGHT, NORMAL);
		} else if (string.equalsIgnoreCase("B")) {
			Serial.println("back");
			itr.move(BACK, NORMAL);
		} else if (string.equalsIgnoreCase("E")) {
			Serial.println("exit");
			itr.move(FRONT, EXIT);
			itr.move(BACK, NORMAL);
		} else if (string.equalsIgnoreCase("SOLVE")) {
			Serial.println("solving....");
			ArrayList<Dir> dirs = Maze::solve();
			for (int i = 0; i < dirs.size(); i++) {
				switch (dirs[i]) {
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
					itr.move(FRONT, NORMAL);
					break;
				case 'b':
				case 'B':
					itr.move(BACK, NORMAL);
					break;
				case 'l':
				case 'L':
					itr.move(LEFT, NORMAL);
					break;
				case 'r':
				case 'R':
					itr.move(RIGHT, NORMAL);
					break;
				case 'e':
				case 'E':
					itr.move(FRONT, EXIT);
					break;
			}
		}
	}
}
}

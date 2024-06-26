/* RgbMatrix.h 
 *
 * Created by GridGurus, May, 2024
 *
 */
#ifndef RgbMatrix_h
#define RgbMatrix_h

#include <Arduino.h>
#include "ShiftOut.h"

#define REGISTER 2

enum class Color {
  RED,
  GREEN,
  BLUE
};

template<int dimension>
class _RgbMatrix {
	private:
		ShiftOut<REGISTER> redShift;
		ShiftOut<REGISTER> blueShift;
		ShiftOut<REGISTER> greenShift;

	public:
		_RgbMatrix() {}

		// setup all pins
		void begin(
			int redLatchPin, 
			int redDataPin,
			int greenLatchPin,
			int greenDataPin,
			int blueLatchPin,
			int blueDataPin,
			int clockPin
		) {
			redShift.begin(
				redLatchPin,
				clockPin,
				redDataPin
			);

			greenShift.begin(
				greenLatchPin,
				clockPin,
				greenDataPin
			);

			blueShift.begin(
				blueLatchPin,
				clockPin,
				blueDataPin
			);
		}

		void setAllLow() {
			redShift.setAllLow();
			greenShift.setAllLow();
			blueShift.setAllLow();
		}

		void writeAllLow() {
			setAllLow();
			writeAll();
		}

		void writeAll(bool print = false) {
			redShift.write();
			greenShift.write();
			blueShift.write();

			if (print) {
				this->print();
			}
		}

		void set(Color color, int index, int value) {
			switch (color) {
				case Color::RED:
					redShift.set(index, value);
					break;
				case Color::GREEN:
					greenShift.set(index, value);
					break;
				case Color::BLUE:
					blueShift.set(index, value);
					break;

				default:
					setAllLow();
					break;
			}
		}

		void write(Color color, bool print = false) {
			switch (color) {
				case Color::RED:
					redShift.write();
					break;

				case Color::GREEN:
					greenShift.write();
					break;

				case Color::BLUE:
					blueShift.write();
					break;
				
				default:
					this->setAllLow();
					break;
			}
			if (print) {
				this->print();
			}
		}

		// Function to print uint16_t as a binary string
		void printBinary(uint16_t value) {
			for (int i = 15; i >= 0; i--) {
				Serial.print((value >> i) & 1);
			}
			Serial.println();
		}

		void print() {
			// Serial.print("Red state: ");
			// printBinary(redShift.state);
			// Serial.print("Green state: ");
			// printBinary(greenShift.state);
			// Serial.print("Blue state: ");
			// printBinary(blueShift.state);
			for (int i = 1; i <= dimension * dimension; i++) {
				if (redShift.get(i - 1)) {
					Serial.print(F(" R "));
				} else if (greenShift.get(i - 1)) {
					Serial.print(F(" G "));
				} else if (blueShift.get(i - 1)) {
					Serial.print(F(" B "));
				} else {
					Serial.print(F(" 0 "));
				}

				// New line
				if (i % dimension == 0) {
					Serial.println();
				} 
				if (i == dimension * dimension) {
					Serial.println();
				}
			}
		}
};

template<int dimension>
class RgbMatrix : public _RgbMatrix<dimension> {};

#endif
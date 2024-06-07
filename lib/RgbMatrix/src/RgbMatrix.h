/* RgbMatrix.h 
 *
 * Created by GridGurus, May, 2024
 *
 */
#ifndef RgbMatrix_h
#define RgbMatrix_h

#include <Arduino.h>
#include <ShiftOut.h>

#define REGISTER_COUNT 2

enum class Color {
  RED,
  GREEN,
  BLUE
};

template<int dimension>
class _RgbMatrix {
	private:
		ShiftOut<REGISTER_COUNT> redShift;
		ShiftOut<REGISTER_COUNT> blueShift;
		ShiftOut<REGISTER_COUNT> greenShift;

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

		void flashWrite(Color color, int durationMilliseconds, int index = -1) {
			if (index != -1) {
				set(color, index, HIGH);
				write(color, false);
			} else {
				setAllHigh(color);
				write(color, false);
			}

			delay(durationMilliseconds);
			write(color);
		}

		void setAllHigh(Color color) {
			switch (color) {
				case Color::RED:
					redShift.setAllHigh();
					break;
				case Color::GREEN:
					greenShift.setAllHigh();
					break;
				case Color::BLUE:
					blueShift.setAllHigh();
					break;

				default:
					setAllLow();
					break;
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

		void write(Color color, bool setAllLow = true) {
			if (setAllLow) {
				this->setAllLow();
			}

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
			print();
		}

		void print() {
			Serial.println("Current matrix state:");
			for (int i = 1; i <= dimension * dimension; i++) {
				if (redShift.get(i - 1)) {
					Serial.print(" R ");
				} else if (greenShift.get(i - 1)) {
					Serial.print(" G ");
				} else if (blueShift.get(i - 1)) {
					Serial.print(" B ");
				} else {
					Serial.print(" 0 ");
				}

				// New line
				if (i % dimension == 0) {
					Serial.println();
				}
			}
		}
};

template<int dimension>
class RgbMatrix : public _RgbMatrix<dimension> {};

#endif
/* RgbMatrix.h 
 *
 * Created by GridGurus, May, 2024
 *
 */
#ifndef RgbMatrix_h
#define RgbMatrix_h

#include <Arduino.h>
#include <ShiftOut.h>

enum class Color {
  RED,
  GREEN,
  BLUE
};

template<int dimension>
class _RgbMatrix {
	private:
		const int dimensions;
		const ShiftOut redShift;
		const ShiftOut blueShift;
		const ShiftOut greenShift;

	public:
		_RgbMatrix() : dimensions(dimension * dimension), redShift(ShiftOut<2>), greenShift(ShiftOut<2>), blueShift(ShiftOut<2>) {}

		// setup all pins
		void begin(
			int redLatchPin, 
			int redDataPin,
			int greedLatchPin,
			int greenDataPin,
			int blueLatchPin,
			int blueDataPin,
			int clockPin,
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

		void flashWrite(Color color, int durationMilliseconds, int index = NULL) {
			if (index != NULL) {
				set(color, index, HIGH);
				write(color, false);
			} else {
				setAllHigh(color);
				write(color, false);
			}

			delay(delayMilliseconds);
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

		void write(Color color, bool setAllLow = true, ShiftType data = NULL) {
			if (setAllLow) {
				setAllLow();
			}

			switch (color) {
				case Color::RED:
					if (data == NULL) {
						redShift.write();
					} else {
						redShift.write(data);
					}
					break;

				case Color::GREEN:
					if (data == NULL) {
						greenShift.write();
					} else {
						greenShift.write(data);
					}
					break;

				case Color::BLUE:
					if (data == NULL) {
						blueShift.write();
					}
					else {
						blueShift.write(data);
					}
					break;
				
				default:
					setAllLow();
					break;
			}
		}
};

template<int dimension>
class RgbMatrix : public _RgbMatrix<dimension> {};

#endif
/* ShiftOut.h - Arduino library that writes values from an 8 bit shift register (74HC195).
 * You can daisy-chain several shift register in order to write up to 64 bleds by only using 4 Arduino pins.
 *
 * Created by GridGurus, May, 2024
 *
 */
#ifndef ShiftOut_h
#define ShiftOut_h

#include <Arduino.h>

template<byte chipCount, typename ShiftType>
class _ShiftOut {
private:
	byte latchPin;
	byte dataPin;
	byte clockPin;

    uint16_t dataWidth;
    int bitOrder;

public:
    _ShiftOut() : state(0), dataWidth(chipCount * 8), bitOrder(MSBFIRST) {}

	ShiftType state;

	// setup all pins
	void begin(int latch, int clock, int data) {
		pinMode(latchPin = latch, OUTPUT);
		pinMode(dataPin = data, OUTPUT);
		pinMode(clockPin = clock, OUTPUT);
        write();
	}

    inline ShiftType getDataWidth() { return dataWidth; }

    void write() {
        digitalWrite(latchPin, LOW);
		for(byte i = 0; i < chipCount; i++) {
			shiftOut(dataPin, clockPin, bitOrder, (byte)(state >> (8 * i))); //1 << index
		}
		digitalWrite(latchPin, HIGH); 
	}
    
	void write(ShiftType data) {
		state = data;
		write();
	}

    void set(int index, int value) {
		if(value == HIGH) {
            state = bitSet(state, index);
        } else {
            state = bitClear(state, index);
        }
	}

	inline boolean get(int index) { return bitRead(state, index); }
	inline void setAllHigh() { state = ~0; }
	inline void setAllLow() { state = 0; }
};

template<byte chipCount>
class ShiftOut : public _ShiftOut<chipCount, uint64_t> {};
template<>
class ShiftOut<1> : public _ShiftOut<1, uint8_t> {};
template<>
class ShiftOut<2> : public _ShiftOut<2, uint16_t> {};

#endif
#pragma once

#include <memory>
#include <vector>

#include "Types.h"

namespace gcyong
{
	class AES
	{
	public:

		AES(std::size_t _keySizeBit = 128) : roundKey(nullptr) {
			keySizeByte = _keySizeBit >> 3;
			switch (_keySizeBit) {
			case 128 :
				round = 10;
				break;
			case 192 :
				round = 12;
				break;
			case 256 :
				round = 14;
				break;
			default :
				round = 0;
				keySizeByte = 0;
			}
		}

		~AES() {
			if (roundKey != nullptr)
				delete[] roundKey;
		}

		void Encrypt(const BYTE* _key, const BYTE* _src, BYTE* _des);
		void Decrypt(const BYTE* _key, const BYTE* _src, BYTE* _des);

	protected :

		static inline UINT convertIndex(UINT _row, UINT _column) { return (_column << 2) + _row; };
		static BYTE multiply(BYTE _f, BYTE _g) {
			BYTE r = (BYTE)0;

			for (int i = 0; i < 8; i++) {
				if (_g & 0x01) {
					r ^= _f;
				}
				_g >>= 1;
				_f = (_f & 0x80) ? ((_f << 1) ^ 0x1B) : (_f << 1);
			}

			return r;
		}

		void SubBytes(BYTE* _bytes);
		void ShiftRows(BYTE* _bytes);
		void MixColumns(BYTE* _bytes);
		void AddRoundKey(BYTE* _bytes, const BYTE* _key);

		void ISubBytes(BYTE* _bytes);
		void IShiftRows(BYTE* _bytes);
		void IMixColumns(BYTE* _bytes);

		void MakeRoundKey(const BYTE* _key);

	private:
		std::size_t keySizeByte;
		std::size_t round;
		BYTE* roundKey;

		const static BYTE SBox[16][16];
		const static BYTE ISBox[16][16];
		const static BYTE CMatrix[4][4];
		const static BYTE ICMatrix[4][4];
		const static BYTE RCon[256];
	};
}
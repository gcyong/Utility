#pragma once

#include <cstddef>

#ifdef __CPP17__

typedef std::byte BYTE;

#else

typedef unsigned char BYTE;

#endif

typedef unsigned int UINT;
typedef unsigned short WORD;
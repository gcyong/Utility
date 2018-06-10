#pragma once

#include "Types.h"

#define HINIBBLE(b) ((BYTE)(((b) >> 4) & 0x0F))
#define LONIBBLE(b) ((BYTE)((b) & 0x0F))
#define XORSWAP(l, r) (l = (r = (l = l ^ r) ^ r) ^ l)
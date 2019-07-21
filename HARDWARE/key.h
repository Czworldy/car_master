#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

#define KEY1 		PEin(2)
#define KEY2 		PEin(3)
#define KEY3 		PEin(4)

#define SW0 		PIin(5)
#define SW1 		PIin(6)
#define SW2 		PIin(7)

void KEY_Init(void);	//IO≥ı ºªØ

#endif

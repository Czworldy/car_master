#ifndef __KEEP_H
#define __KEEP_H

#include "sys.h"
#include "MyTypeDef.h"

void SetKeep(struct Point *end_point, double aim_radian, double speed_max);
void Keep(struct PID *Pid_ang, struct PID *Pid_dis);

#endif

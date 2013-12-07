#ifndef ROBOT_H
#define ROBOT_H

void* initRobot(void* r);

struct ROBOT {
	OPERATION op;
	CASE* cs;
};
#endif

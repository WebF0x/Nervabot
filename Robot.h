/*
 * Robot.h
 *
 *  Created on: 2014-10-01
 *      Author: dupm2216
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libarmus.h>

class Robot
{
public:
	Robot();
	virtual ~Robot();
	void calibrateWheels(int millis);
	void dispSpeedDifferences();
	void avancer(int targetSpeed);
	void stop();

private:
	float m_leftWheelSlope;
	float m_rightWheelSlope;
	float m_leftWheelOffset;
	float m_rightWheelOffset;
};

#endif /* ROBOT_H_ */

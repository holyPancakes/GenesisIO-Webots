// File:          bioloid_dog_NN.cpp
// Date:          10 April 2019
// Description:   Controller for Bioloid Dog robot using Neural Networks (Configured using controllerArgs passed by Supervisor)
// Author:        Maru Gabriel S. Baul
// Modifications: 10 April 2019

#include <webots/Camera.hpp>
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Keyboard.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/DistanceSensor.hpp>

#include <stdlib.h>
#include <time.h>

#include <list>
#include <string>

#define NUM_OF_MOTORS 16
#define NUM_OF_DS 3

// All the webots classes are defined in the "webots" namespace
using namespace webots;
using std::string;
using std::list;
using std::cout;

// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv)
{
	srand(time(NULL));

	// create the Robot instance.
	Robot *robot = new Robot();

	// get the time step of the current world.
	int timeStep = (int) robot->getBasicTimeStep();

	//get references to devices
	//Keyboard 
	Keyboard *kb = robot->getKeyboard();
	kb->enable(timeStep);

	//Motors and Position Sensors
	std::list<Motor *> motorList;
	string motorNames[NUM_OF_MOTORS] = {"pelvis","front_left_1","front_right_1","front_left_2","front_right_2","front_left_3","front_right_3","back_left_1","back_right_1","back_left_2","back_right_2","back_left_3","back_right_3","neck_1","neck_2","head"};
	for(string mn : motorNames){
		Motor* m = robot->getMotor(mn);
		m->getPositionSensor()->enable(timeStep);
		double t = m->getMaxTorque()/500000;
		m->setTorque(t - ((rand()%100+1)/100)*(2*t) );
		printf("[%s] position => (%f) \n", mn.c_str(), m->getPositionSensor()->getValue());
		motorList.push_back(m);	
	};
	
	//Distance Sensors
	std::list<DistanceSensor *> dsList;
	string dsNames[NUM_OF_DS] = {"ds0","ds1","ds2"};
	for(string dsn : dsNames){
		DistanceSensor* ds = robot->getDistanceSensor(dsn);
		ds->enable(timeStep);
		printf("[%s] position => (%f) \n", dsn.c_str(), ds->getValue());	
		dsList.push_back(ds);
	};

	//Camera
	Camera *cam = robot->getCamera("camera");
	cam->enable(timeStep);

	//


	// Main loop:
	// - perform simulation steps until Webots is stopping the controller
	while (robot->step(timeStep) != -1) {
		// Read the sensors:
		
		// Process sensor data

		// Functions to send actuator commands, like:

	};

	// Exit cleanup code.

	delete robot;
	return 0;
}

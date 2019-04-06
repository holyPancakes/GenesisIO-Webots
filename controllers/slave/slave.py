# Copyright 1996-2018 Cyberbotics Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
This controller gives to its robot the following behavior:
According to the messages it receives, the robot change its
behavior.
"""

from controller import Robot


class Slave (Robot):
    
    timeStep = 32
    maxSpeed = 20.0
    motors = []
    distanceSensors = []

    def boundSpeed(self, speed):
        return max(-self.maxSpeed, min(self.maxSpeed, speed))

    def initialization(self):
        self.motors.append(self.getMotor("left wheel motor"))
        self.motors.append(self.getMotor("right wheel motor"))
        self.motors[0].setPosition(float("inf"))
        self.motors[1].setPosition(float("inf"))
        self.motors[0].setVelocity(0.0)
        self.motors[1].setVelocity(0.0)
        for dsnumber in range(0, 2):
            self.distanceSensors.append(self.getDistanceSensor('ds' + str(dsnumber)))
            self.distanceSensors[-1].enable(self.timeStep)

    def run(self):
        while True:
           
            delta = self.distanceSensors[0].getValue() - self.distanceSensors[1].getValue()
            speeds = [0.0, 0.0]

            
            speeds[0] = self.boundSpeed(self.maxSpeed / 2 + 0.1 * delta)
            speeds[1] = self.boundSpeed(self.maxSpeed / 2 - 0.1 * delta)
            
            
            self.motors[0].setVelocity(speeds[0])
            self.motors[1].setVelocity(speeds[1])

            # Perform a simulation step, quit the loop when
            # Webots is about to quit.
            if self.step(self.timeStep) == -1:
                break


controller = Slave()
controller.initialization()
controller.run()

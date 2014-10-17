#include "leaplistener.hpp"

void LeapListener::onInit(const Controller& controller) 
{
	std::cout << "Initialized" << std::endl;
}
void LeapListener::onConnect(const Controller& controller) 
{
	std::cout << "Connected" << std::endl;
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	controller.enableGesture(Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	controller.enableGesture(Gesture::TYPE_SWIPE);
}
void LeapListener::onDisconnect(const Controller& controller) 
{
	// Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;
}
void LeapListener::onExit(const Controller& controller) 
{
	std::cout << "Exited" << std::endl;
}
void LeapListener::onFrame(const Controller& controller) 
{
	const Frame frame = controller.frame();
	if (frame.fingers().count() > 0) 
	{
		fingers = frame.fingers();
		int finger_count = frame.fingers().count();
		for (int f = 0; f < finger_count; f++) 
		{
			Finger finger = frame.fingers()[f];
			if (finger.isValid())
			{
				float x = finger.tipPosition().x;
				float y = finger.tipPosition().y;
				float z = finger.tipPosition().z;

				float velx = finger.tipVelocity().x;
				float vely = finger.tipVelocity().y;
				float velz = finger.tipVelocity().z;
				switch(finger.type())
				{
					case Finger::TYPE_THUMB: 
						fingers_pos[0] = ofVec3f(x, y, z);
						fingers_vel[0] = ofVec3f(velx, vely, velz);
						// printf("%s\n", "TYPE_THUMB"); 
						break;
					case Finger::TYPE_INDEX: 
						fingers_pos[1] = ofVec3f(x, y, z);
						fingers_vel[1] = ofVec3f(velx, vely, velz);
						// printf("%s\n", "TYPE_INDEX"); 
						break;
					case Finger::TYPE_MIDDLE: 
						fingers_pos[2] = ofVec3f(x, y, z);
						fingers_vel[2] = ofVec3f(velx, vely, velz);
						// printf("%s\n", "TYPE_MIDDLE"); 
						break;
					case Finger::TYPE_RING: 
						fingers_pos[3] = ofVec3f(x, y, z);
						fingers_vel[3] = ofVec3f(velx, vely, velz);
						// printf("%s\n", "TYPE_RING"); 
						break;
					case Finger::TYPE_PINKY: 
						fingers_pos[4] = ofVec3f(x, y, z);
						fingers_vel[4] = ofVec3f(velx, vely, velz);
						// printf("%s\n", "TYPE_PINKY"); 
						break;
				}				
			}
    	}
	}
}

void LeapListener::onFocusGained(const Controller& controller) 
{
	std::cout << "Focus Gained" << std::endl;
}

void LeapListener::onFocusLost(const Controller& controller) 
{
	std::cout << "Focus Lost" << std::endl;
}
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
	//Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;
}
void LeapListener::onExit(const Controller& controller) 
{
	std::cout << "Exited" << std::endl;
}
void LeapListener::onFrame(const Controller& controller) 
{
	const Frame frame = controller.frame();
	if (!frame.hands().empty()) 
	{
		// Get the first hand
		const Hand hand = frame.hands()[0];

		// Check if the hand has any fingers
		const FingerList fingers = hand.fingers();
		if (!fingers.empty()) 
		{
			// Calculate the hand's average finger tip position
			Vector avgPos;
			for (int i = 0; i < fingers.count(); ++i) 
			{
				avgPos += fingers[i].tipPosition();
			}
			avgPos /= (float)fingers.count();
			std::cout << "Hand has " << fingers.count()
					  << " fingers, average finger tip position" << avgPos << std::endl;
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
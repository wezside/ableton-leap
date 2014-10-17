#pragma once

#include "Leap.h"
#include "ofVec3f.h"

using namespace Leap;

class LeapListener : public Listener 
{
	public:
		virtual void onInit(const Controller&);
		virtual void onConnect(const Controller&);
		virtual void onDisconnect(const Controller&);
		virtual void onExit(const Controller&);
		virtual void onFrame(const Controller&);
		virtual void onFocusGained(const Controller&);
		virtual void onFocusLost(const Controller&);

		FingerList fingers;
		ofVec3f fingers_pos[5];
		ofVec3f fingers_vel[5];
};
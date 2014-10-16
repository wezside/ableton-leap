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

		ofVec3f hand_pos;
};
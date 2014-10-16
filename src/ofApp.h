#pragma once

#define APP_SCALE 0.2
#define PARTICLES_NUM 100000

#include "ofMain.h"
#include "ofShader.h"
#include "repeller.hpp"
#include "attractor.hpp"
#include "particlesystem.hpp"
#include "leaplistener.hpp"

class ofApp : public ofBaseApp
{

	public:
		void exit();
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofFbo fbo;
		ofShader shader;
		ofCamera camera;
		wezside::ParticleSystem ps;
		wezside::Force* gravity;
		wezside::Repeller* repeller;

		LeapListener listener;
		Controller controller;

		bool debug;
};

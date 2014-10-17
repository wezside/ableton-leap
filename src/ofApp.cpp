#include "ofApp.h"

void ofApp::exit()
{
	delete gravity;
	delete repeller;
	ps.destroy();
	controller.removeListener(listener);

	for (std::vector<wezside::Repeller*>::iterator it = repellers.begin(); it != repellers.end(); ++it)
	{
		delete *it;
	}
}
void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(false);

	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	fbo.begin();
	ofClear(255,255,255, 0);
	fbo.end();

	// Set up forces
	gravity = new wezside::Force(0.0f, 0.0001f, 0.0f);
	for (int i = 0; i < 5; ++i)
	{
	   repellers.push_back(new wezside::Repeller(0.0, 0.0, -500.0f));
	}
	repeller = new wezside::Repeller(0.0, 0.0, -500.0f);

	// Create particle and any constant forces
	for (int i = 0; i < PARTICLES_NUM; ++i)
	{
		wezside::Particle* p = new wezside::Particle();
		p->init();
		ps.addParticle(p);
	}
	ps.init();
	shader.load(ofToDataPath("particle.vert"), ofToDataPath("particle.frag"));
	camera.setFov(60);

	cx = ofGetWindowWidth() * 0.5;
	cy = ofGetWindowHeight() * 0.5;
	cw = ofGetWidth();
	ch = ofGetHeight();
	controller.addListener(listener);
}
void ofApp::update()
{
	ps.applyForce(gravity);
	for (int i = 0; i < 5; ++i)
	{
		float xpos = ofMap(listener.fingers_pos[i].x, -300.0f, 300.0f, 0.0f, ofGetWidth(), true);
		float ypos = ofMap(listener.fingers_pos[i].y, 500.0f, 0.0f, 0.0f, ofGetHeight(), true);
		float zpos = ofMap(listener.fingers_pos[i].z, -300.0f, 300.0f, -450.0f, -550.0f, true);

		float velx = ofMap(listener.fingers_vel[i].x, -300.0f, 300.0f, 0.0f, ofGetWidth(), true);
		float vely = ofMap(listener.fingers_vel[i].y, 500.0f, 0.0f, 0.0f, ofGetHeight(), true);
		float velz = ofMap(listener.fingers_vel[i].z, -300.0f, 300.0f, -450.0f, -550.0f, true);

		ofVec3f vel = ofVec3f(listener.fingers_vel[i].x, listener.fingers_vel[i].y, listener.fingers_vel[i].z);
		// ofLog(OF_LOG_NOTICE, "%f, %f, %f", vel.x, vel.y, vel.z);

		ofVec3f tmp = ofVec3f(xpos, ypos, zpos);
		repellers[i]->setTarget(tmp);
		repellers[i]->forcemass = 10.0f * vely;
		repellers[i]->forcemass_limit = repellers[i]->forcemass;
		ps.applyForce(repellers[i]);
	}
	/*repellers[0]->forcemass = 10000.0f;
	repellers[0]->forcemass_limit = 10000.0f;
	ps.applyForce(repellers[0]);*/

	// repeller->forcemass = 10000.0f;
	// repeller->forcemass_limit = 10000.0f;
	// ps.applyForce(repeller);

	ps.update();
}
void ofApp::draw()
{
	fbo.begin();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofBackground(ofColor(4, 15, 25, 22));
			camera.begin();
			ofTranslate(0, 0, 0);
			ofScale(1, -1, 1);
				shader.begin();
				shader.setUniform1f("u_size", 0.35);
				shader.setUniform1i("u_screen_x", ofGetWidth());
				shader.setUniform1i("u_screen_y", ofGetHeight());
				shader.setUniformMatrix4f("modelViewMatrix", camera.getModelViewMatrix());
				shader.setUniformMatrix4f("modelViewProjectionMatrix", camera.getModelViewProjectionMatrix());
				ps.draw();
				shader.end();
				if (debug)
				{
					// Draw some debug info
				}
			camera.end();
		ofDisableBlendMode();
	fbo.end();
	fbo.draw(0, 0);
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 2) + "fps");
}
void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key)
{
	switch (key)
	{
		case 'd': debug = !debug; break;
	}
}
void ofApp::mouseMoved(int x, int y )
{
	// ps.setMouseXY(x, y);
}
void ofApp::mouseDragged(int x, int y, int button){}	
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}

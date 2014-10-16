#include "ofApp.h"

void ofApp::exit()
{
	delete gravity;
	delete repeller;	
	ps.destroy();
    controller.removeListener(listener);
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

    controller.addListener(listener);
}
void ofApp::update()
{
	ps.applyForce(gravity);
	repeller->forcemass = 10000.0f;
    repeller->forcemass_limit = 10000.0f;
	ps.applyForce(repeller);
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
	ps.setMouseXY(x, y);
}
void ofApp::mouseDragged(int x, int y, int button){}	
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}

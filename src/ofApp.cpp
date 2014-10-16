#include "ofApp.h"

void ofApp::exit()
{
	delete stream;
	delete repeller;	
	delete attractor;
	delete attractor2;
	delete attractor3;
	delete attractor4;
	ps.destroy();
}
void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(false);
	// ofDisableArbTex();

	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	fbo.begin();
	ofClear(255,255,255, 0);
	fbo.end();

	// Set up forces
	stream = new wezside::Force(-0.00000001, 0.0, 0.0);
	gravity = new wezside::Force(0.0f, 0.0001f, 0.0f);
	repeller = new wezside::Repeller(0.0, 0.0, -500.0f);
	attractor = new wezside::Attractor(0.0, -10.0, -500.0);
	attractor2 = new wezside::Attractor(-200.0, 100.0, -500.0);
	attractor3 = new wezside::Attractor(300.0, -50.0, -400.0);
	attractor4 = new wezside::Attractor(-500.0, -250.0, -600.0);

	// Create partocle and any Constant forces
	for (int i = 0; i < PARTICLES_NUM; ++i)
	{
		wezside::Particle* p = new wezside::Particle();
		p->init();
		// p->addForce(gravity);
		ps.addParticle(p);
	}
	ps.init();
	shader.load(ofToDataPath("particle.vert"), ofToDataPath("particle.frag"));
	camera.setFov(60);
}
void ofApp::update()
{
	if (mouse_pressed == 1)
	{
		ps.applyForce(gravity);
		if (repell_keydown)
		{
			repeller->forcemass = 10000.0f;
			repeller->forcemass_limit = 10000.0f;
			ps.applyForce(repeller);
		} 

	/*	attractor->forcemass = 1000.0f;
		attractor->forcemass_limit = 1100.0f;
		ps.applyForce(attractor);

		attractor2->forcemass = 1000.0f;
		attractor2->forcemass_limit = 1100.0f;
		ps.applyForce(attractor2);

		attractor3->forcemass = 800.0f;
		attractor3->forcemass_limit = 900.0f;
		ps.applyForce(attractor3);

		attractor4->forcemass = 1500.0f;
		attractor4->forcemass_limit = 1600.0f;
		ps.applyForce(attractor4);*/

	}
	else
	{
		/*if (attractor->forcemass > 30.0f) attractor->forcemass -= 2.0f;
		if (attractor2->forcemass > 30.0f) attractor2->forcemass -= 2.0f;
		if (attractor3->forcemass > 30.0f) attractor3->forcemass -= 2.0f;
		if (attractor4->forcemass > 30.0f) attractor4->forcemass -= 2.0f;
		ps.applyForce(attractor);
		ps.applyForce(attractor2);
		ps.applyForce(attractor3);
		ps.applyForce(attractor4);*/
	} 
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
				// attractor->draw();
				// attractor2->draw();
				// attractor3->draw();
				// attractor4->draw();
				// repeller->draw();
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
		case '1': repell_keydown = !repell_keydown; ofLog(OF_LOG_NOTICE, "%s", repell_keydown ? "Repelling": ""); break;
	}
}
void ofApp::mouseMoved(int x, int y )
{
	ps.setMouseXY(x, y);
}
void ofApp::mouseDragged(int x, int y, int button){}	
void ofApp::mousePressed(int x, int y, int button)
{
	// mouse_pressed = 1;
}
void ofApp::mouseReleased(int x, int y, int button)
{
	mouse_pressed = !mouse_pressed;
	ofLog(OF_LOG_NOTICE, "%s", mouse_pressed == 1 ? "Mouse pressed" : "");
}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}

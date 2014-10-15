#include "ofApp.h"

void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	shader.load("particle");
}

void ofApp::update(){}

void ofApp::draw()
{
	ofSetColor(255);
    shader.begin();
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();

    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2) + "fps");
}

void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
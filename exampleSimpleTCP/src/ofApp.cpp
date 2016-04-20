#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	this->clientThread = thread([this]() {
		this->client.init("localhost", 5000);
		while (this->threadsRunning) {
			this->client.update();
		}
	});

	this->serverThread = thread([this]() {
		this->server.init(5000);
		while (this->threadsRunning) {
			this->server.update();
		}
	});
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(40, 0);

	stringstream message;

	message << "Client" << endl;
	message << "======" << endl;
	message << "isConnected = " << (this->client.isConnected() ? "true" : "false") << endl;

	message << endl;
	
	message << "Server" << endl;
	message << "======" << endl;
	message << "isConnected = " << (this->server.isConnected() ? "true" : "false") << endl;

	ofDrawBitmapString(message.str(), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::exit() {
	this->threadsRunning = false;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

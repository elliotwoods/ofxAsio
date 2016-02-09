#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// When binding a server, we must use the server's constructor
	// We use an empty pointer to represent that no server is bound.
	this->receiver = make_shared<ofxAsio::UDP::Server>(4444);
}

//--------------------------------------------------------------
void ofApp::update(){

	cout << "Sending" << endl;
	cout << "=======" << endl;
	cout << endl;
	//send a DataGram (i.e. a message)
	{
		//make the DataGram
		auto dataGram = make_shared<ofxAsio::UDP::DataGram>();
		dataGram->setMessage("I am the message."); //--set the message content
		dataGram->setEndPoint(ofxAsio::UDP::EndPoint("127.0.0.1", 4444)); //--set where the message will be sent to

		//send the DataGram
		this->sender.send(dataGram);

		cout << dataGram->getMessage() << endl;
		cout << "Sent to : " << dataGram->getEndPoint() << endl;
	}
	cout << endl;
	
	cout << "Receiving" << endl;
	cout << "=========" << endl;
	cout << endl;
	//try to receive data
	{
		//receive a DataGram
		auto dataGram = this->receiver->receive();

		cout << dataGram->getMessage() << endl;
		cout << "Arrived from : " << dataGram->getEndPoint() << endl;
	}
	cout << endl;


	cout << endl;
	cout << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){

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
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

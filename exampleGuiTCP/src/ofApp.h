#pragma once

#include "ofMain.h"
#include "ofxAsio.h"
#include "ofxCvGui.h"

struct Connection {
	virtual ofxAsio::TCP::Socket & getSocket() = 0;
	std::thread thread;

	bool threadRunning = true;
};

struct Server : Connection {
	ofxAsio::TCP::Server socket;
	ofParameter<int> port{ "Port", 5000 };

	ofxAsio::TCP::Socket & getSocket() override {
		return this->socket;
	}
};

struct Client : Connection {
	ofxAsio::TCP::Client socket;
	ofParameter<string> address{ "Address", "localhost" };
	ofParameter<int> port{ "Port", 5000 };
	
	ofxAsio::TCP::Socket & getSocket() override {
		return this->socket;
	}
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void rebuildGui();

		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		virtual void exit() override;

		ofxCvGui::Builder gui;

		bool threadsRunning = true;

		set<shared_ptr<Connection>> connections;
};

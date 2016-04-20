#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	this->gui.init();

	this->rebuildGui();
}

//--------------------------------------------------------------
void ofApp::rebuildGui() {
	this->gui.clear();

	auto widgets = this->gui.addWidgets();

	widgets->addTitle("TCP Connections Tests");
	widgets->addButton("Add server", [this]() {
		auto connection = make_shared<Server>();

		connection->thread = thread([connection]() {
			while (connection->threadRunning) {
				connection->getSocket().update();
			}
		});

		this->connections.insert(connection);
		this->rebuildGui();
	});
	widgets->addButton("Add client", [this]() {
		auto connection = make_shared<Client>();

		connection->thread = thread([connection]() {
			while (connection->threadRunning) {
				connection->getSocket().update();
			}
		});

		this->connections.insert(connection);
		this->rebuildGui();
	});

	for (auto connection : this->connections) {
		{
			auto panel = this->gui.addWidgets();
			
			{
				auto client = dynamic_pointer_cast<Client>(connection);
				if (client) {
					panel->addTitle("Client");
					panel->addEditableValue<string>(client->address);
					panel->addEditableValue<int>(client->port);
					panel->addButton("Init", [client]() {
						client->socket.init(client->address, client->port);
					});
				}
			}

			{
				auto server = dynamic_pointer_cast<Server>(connection);
				if (server) {
					panel->addTitle("Server");
					panel->addEditableValue<int>(server->port);
					panel->addButton("Init", [server]() {
						server->socket.init(server->port);
					});
				}
			}

			panel->addIndicator("Active", [connection]() {
				if (connection->getSocket().isActive()) {
					return ofxCvGui::Widgets::Indicator::Status::Good;
				}
				else {
					return ofxCvGui::Widgets::Indicator::Status::Clear;
				}
			});
			panel->addIndicator("Connected", [connection]() {
				if (connection->getSocket().isConnected()) {
					return ofxCvGui::Widgets::Indicator::Status::Good;
				}
				else {
					return ofxCvGui::Widgets::Indicator::Status::Clear;
				}
			});
			panel->addButton("Delete", [this, connection]() {
				this->connections.erase(connection);
				this->rebuildGui();
			});
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){

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
void ofApp::exit() {
	this->threadsRunning = false;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

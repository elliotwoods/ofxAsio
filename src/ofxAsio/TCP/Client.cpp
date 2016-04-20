#include "Client.h"

using namespace asio;
using namespace asio::ip;

namespace ofxAsio {
	namespace TCP {
		//----------
		void Client::init(string address, int port) {
			this->active = true;
			this->address = address;
			this->port = port;
		}

		//----------
		void Client::update() {
			if (!this->active) {
				return;
			}

			if (!this->isConnected()) {
				tcp::resolver resolver(this->ioService);

				tcp::resolver::query query(address, ofToString(port));
				tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
				tcp::resolver::iterator end;

				asio::error_code error = asio::error::host_not_found;
				while (error && endpoint_iterator != end) {
					this->socket.close();
					this->socket.connect(endpoint_iterator->endpoint(), error);
					endpoint_iterator++;
				}
				if (error) {
					ofLogNotice("ofxAsio::TCP::Client::connect") << "Connection failed : " << error.message();
				}
			}
		}
	}
}
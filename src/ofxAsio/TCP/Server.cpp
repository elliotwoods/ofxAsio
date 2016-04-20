#include "Server.h"

using namespace asio;
using namespace asio::ip;

namespace ofxAsio {
	namespace TCP {
		//----------
		void Server::init(int port) {
			this->active = true;
			this->port = port;
		}

		//----------
		void Server::update() {
			if (!this->active) {
				return;
			}

			if (!this->isConnected()) {
				this->acceptor = make_unique<tcp::acceptor>(this->ioService, tcp::endpoint(tcp::v4(), port));
				this->acceptor->accept(this->socket);
			}
		}
	}
}
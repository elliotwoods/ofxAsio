#pragma once

#include "Socket.h"

namespace ofxAsio {
	namespace TCP {
		class Server : public Socket {
		public:
			void init(int port);
			void update() override;
		protected:
			int port;
			unique_ptr<asio::ip::tcp::acceptor> acceptor;
		};
	}
}
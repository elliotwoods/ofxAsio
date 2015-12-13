#pragma once

#include "../Includes.h"
#include "DataGram.h"

namespace ofxAsio {
	namespace UDP {
		class Socket {
		public:
			Socket();
			Socket(int port);

			shared_ptr<DataGram> receive(size_t bufferSize = 9216);

			bool send(shared_ptr<DataGram>);
		protected:
			asio::io_service ioService;
			asio::ip::udp::socket socket;
		};
	}
}
#pragma once

#include "EndPoint.h"

#include "../Includes.h"
#include <string>

namespace ofxAsio {
	using namespace std;

	namespace UDP {
		class Server {
		public:
			struct DataGram {
				string getMessageString();

				asio::streambuf streamBuffer;
				EndPoint endPoint;
			};

			Server(int port);
			shared_ptr<DataGram> receive(size_t bufferSize = 9216);

		protected:
			asio::io_service ioService;
			asio::ip::udp::socket socket;
		};
	}
}
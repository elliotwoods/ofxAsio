#pragma once

#include "../Includes.h"
#include "DataGram.h"

namespace ofxAsio {
	namespace UDP {
		class Socket {
		public:
			struct AsyncArguments {
				bool success;
				string error;
				shared_ptr<DataGram> dataGram;
			};

			Socket();
			Socket(int port);
			~Socket();

			shared_ptr<DataGram> receive(size_t bufferSize = 9216);

			void asyncReceiveOnce(const function<void(AsyncArguments)> &, size_t bufferSize = 9216);
			void asyncReceiveAll(const function<void(AsyncArguments)> &, size_t bufferSize = 9216);
			
			bool send(shared_ptr<DataGram>);
		protected:
			asio::io_service ioService;
			asio::io_service::work work;
			asio::ip::udp::socket socket;

			std::thread asyncThread;

			struct AsyncIncoming {
				string buffer;
				asio::ip::udp::endpoint endpoint;
			} asyncIncoming;
		};
	}
}
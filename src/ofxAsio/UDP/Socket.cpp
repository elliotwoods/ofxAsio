#include "Socket.h"

namespace ofxAsio {
	namespace UDP {
		//----------
		Socket::Socket() :
		socket(this->ioService) {
			socket.open(asio::ip::udp::v4());
		}

		//----------
		Socket::Socket(int port) :
			socket(this->ioService, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)) {

		}

		//----------
		shared_ptr<DataGram> Socket::receive(size_t bufferSize) {
			asio::error_code errorCode;
			auto dataGram = make_shared<DataGram>();
			auto & message = dataGram->getMessage();
			message.resize(bufferSize);

			auto mutableBuffer = asio::buffer(message.data(), message.size());

			auto receivedSize = this->socket.receive_from(mutableBuffer, dataGram->getEndPoint().getEndPoint(), 0, errorCode);

			if (errorCode) {
				//return empty pointer if we failed to receive
				ofLogError("ofxAsio::UDP::Socket::receive") << "Cannot receive data. " << asio::system_error(errorCode).what();
				return shared_ptr<DataGram>();
			}
			else {
				//return pointer to a DataGram object if succeed
				message.resize(receivedSize);
				return dataGram;
			}
		}

		//----------
		bool Socket::send(shared_ptr<DataGram> dataGram) {
			asio::error_code errorCode;
			const auto & message = dataGram->getMessage();
			const auto & endPoint = dataGram->getEndPoint().getEndPoint();

			//this is a wrapper not a copy
			auto buffer = asio::buffer(message.data(), message.size());

			this->socket.send_to(buffer, endPoint, 0, errorCode);

			if (errorCode) {
				ofLogError("ofxAsio::UDP::Socket::send") << "Cannot send data. " << asio::system_error(errorCode).what();
				return false;
			}
			else {
				return true;
			}
		}
	}
}
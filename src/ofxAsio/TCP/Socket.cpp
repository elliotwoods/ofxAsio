#include "Socket.h"

using namespace asio;
using namespace asio::ip;

namespace ofxAsio {
	namespace TCP {
		//----------
		Socket::Socket()
			: socket(ioService) {

		}

		//----------
		bool Socket::isActive() const {
			return this->active;
		}

		//----------
		bool Socket::isConnected() const {
			return this->socket.is_open();
		}

		//----------
		shared_ptr<DataGram> Socket::receive(size_t bufferSize) {
			asio::error_code errorCode;
			auto dataGram = make_shared<DataGram>();
			auto & message = dataGram->getMessage();
			message.resize(bufferSize);

			auto mutableBuffer = asio::buffer(message.data(), message.size());

			auto receivedSize = this->socket.read_some(mutableBuffer, errorCode);

			if (errorCode) {
				//return empty pointer if we failed to receive
				ofLogError("ofxAsio::TCP::Socket::receive") << "Cannot receive data. " << asio::system_error(errorCode).what();
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

			//this is a wrapper not a copy
			auto buffer = asio::buffer(message.data(), message.size());

			this->socket.send(buffer, 0, errorCode);

			if (errorCode) {
				ofLogError("ofxAsio::TCP::Socket::send") << "Cannot send data. " << asio::system_error(errorCode).what();
				return false;
			}
			else {
				return true;
			}
		}
	}
}
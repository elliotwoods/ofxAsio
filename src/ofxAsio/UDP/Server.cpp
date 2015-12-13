#include "Server.h"

#include "ofUtils.h"

namespace ofxAsio {
	namespace UDP {
#pragma mark Server::DataGram
		//----------
		string Server::DataGram::getMessageString() {
			string result;

			istream messageStream(&this->streamBuffer);
			messageStream >> result;
			return result;
		}

#pragma mark Server
		//----------
		Server::Server(int port) : 
		socket(this->ioService, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)) {
			
		}

		//----------
		shared_ptr<Server::DataGram> Server::receive(size_t bufferSize) {
			asio::error_code errorCode;
			auto dataGram = make_shared<DataGram>();

			auto mutableBuffer = dataGram->streamBuffer.prepare(bufferSize);
			auto receivedSize = this->socket.receive_from(mutableBuffer, dataGram->endPoint.getEndPoint(), 0, errorCode);

			if (errorCode) {
				//return empty pointer if we failed to receive
				ofLogError("ofxAsio::UDP::Server::receive") << "Cannot recieve data. " << asio::system_error(errorCode).what();
				return shared_ptr<Server::DataGram>();
			}
			else {
				//return pointer to a DataGram object if succeed
				dataGram->streamBuffer.commit(receivedSize);
				return dataGram;
			}
		}
	}
}
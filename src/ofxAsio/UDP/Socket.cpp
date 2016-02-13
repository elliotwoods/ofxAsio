#include "Socket.h"

namespace ofxAsio {
	namespace UDP {
		//----------
		Socket::Socket()
			: socket(this->ioService)
			, work(this->ioService)
		{
			socket.open(asio::ip::udp::v4());

			this->asyncThread = thread([this]() {
				this->ioService.run();
			});
		}

		//----------
		Socket::Socket(int port)
			: socket(this->ioService, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
			, work(this->ioService)
		{
			this->asyncThread = thread([this]() {
				this->ioService.run();
			});
		}

		//----------
		Socket::~Socket() {
			this->ioService.stop();
			this->asyncThread.join();
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
		void Socket::asyncReceiveOnce(const function<void(AsyncArguments)> & callback, size_t bufferSize) {
			this->asyncIncoming.buffer.resize(bufferSize);
			this->socket.async_receive_from(
				asio::buffer(this->asyncIncoming.buffer),
				this->asyncIncoming.endpoint,
				[this, callback](asio::error_code errorCode,
					size_t size) {
				if (errorCode) {
					AsyncArguments args = {
						false,
						asio::system_error(errorCode).what(),
						shared_ptr<DataGram>()
					};
					callback(args);
				}
				else {
					auto dataGram = make_shared<DataGram>();
					dataGram->getMessage().set(this->asyncIncoming.buffer);
					dataGram->setEndPoint(this->asyncIncoming.endpoint);

					AsyncArguments args = {
						true,
						asio::system_error(errorCode).what(),
						dataGram
					};
					callback(args);
				}
			});
		}

		//----------
		void Socket::asyncReceiveAll(const function<void(AsyncArguments)> & callback, size_t bufferSize) {
			this->asyncReceiveOnce([this, callback, bufferSize](AsyncArguments args) {
				asyncReceiveAll(callback, bufferSize);
				callback(args);
			});
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
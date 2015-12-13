#include "EndPoint.h"

namespace ofxAsio {
	namespace UDP {
		//----------
		EndPoint::EndPoint() {

		}

		//----------
		EndPoint::EndPoint(asio::ip::udp::endpoint & endPoint) :
		endPoint(endPoint) {

		}

		//----------
		EndPoint::EndPoint(string ipAddressString, int port) {
			auto ipAddress = asio::ip::address::from_string(ipAddressString);
			auto endPoint = asio::ip::udp::endpoint(ipAddress, port);
			this->endPoint = endPoint;
		}

		//----------
		asio::ip::udp::endpoint & EndPoint::getEndPoint() {
			return this->endPoint;
		}

		//----------
		const asio::ip::udp::endpoint & EndPoint::getEndPoint() const {
			return this->endPoint;
		}
	}
}
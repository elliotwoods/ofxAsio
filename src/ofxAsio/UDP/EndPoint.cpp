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
		asio::ip::udp::endpoint & EndPoint::getEndPoint() {
			return this->endPoint;
		}

		//----------
		const asio::ip::udp::endpoint & EndPoint::getEndPoint() const {
			return this->endPoint;
		}
	}
}
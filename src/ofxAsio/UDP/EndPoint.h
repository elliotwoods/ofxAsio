#pragma once

#include "../Includes.h"

namespace ofxAsio {
	namespace UDP {
		class EndPoint {
		public:
			EndPoint();
			EndPoint(asio::ip::udp::endpoint &);
			EndPoint(string ipAddress, int port);

			asio::ip::udp::endpoint & getEndPoint();
			const asio::ip::udp::endpoint & getEndPoint() const;
		protected:
			asio::ip::udp::endpoint endPoint;
		};

		ostream & operator<<(ostream &, const EndPoint &);
	}
}
#pragma once

#include "Socket.h"

namespace ofxAsio {
	namespace TCP {
		class Client : public Socket {
		public:
			void init(string address, int port);
			void update() override;
		protected:
			string address;
			int port;
		};
	}
}
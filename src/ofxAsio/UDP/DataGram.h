#pragma once

#include "../DataGram.h"
#include "EndPoint.h"

namespace ofxAsio {
	namespace UDP {
		class DataGram : public ofxAsio::DataGram {
		public:
			void setEndPoint(const EndPoint &);
			EndPoint & getEndPoint();
			const EndPoint & getEndPoint() const;
		protected:
			EndPoint endPoint;
		};
	}
}
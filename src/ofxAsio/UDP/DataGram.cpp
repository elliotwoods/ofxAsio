#include "DataGram.h"

namespace ofxAsio {
	namespace UDP {
		//----------
		void DataGram::setEndPoint(const EndPoint & endPoint) {
			this->endPoint = endPoint;
		}

		//----------
		EndPoint & DataGram::getEndPoint() {
			return this->endPoint;
		}

		//----------
		const EndPoint & DataGram::getEndPoint() const {
			return this->endPoint;
		}
	}
}
#include "DataGram.h"

#include "ofUtils.h"

using namespace std;

namespace ofxAsio {
	namespace UDP {
		//----------
		DataGram::DataGram() {
			this->message = new string();
			this->localAllocation = true;
		}

		//----------
		DataGram::~DataGram() {
			if (this->localAllocation) {
				delete this->message;
				this->message = nullptr;
				this->localAllocation = false;
			}
		}

		//----------
		void DataGram::setMessage(const string & message) {
			if (this->localAllocation) {
				*this->message = message;
			}
			else {
				ofLogError("ofxAsio::UDP::DataGram::setMessage") << "Cannot call setMessage when you are using an external message buffer (setMessageExternal)";
			}
		}

		//----------
		void DataGram::setMessageExternal(const string & message) {
			if (this->localAllocation) {
				delete this->message;
				this->localAllocation = false;
			}
			this->message = & const_cast<string &>(message);
		}

		//----------
		string & DataGram::getMessage() {
			return *message;
		}

		//----------
		const string & DataGram::getMessage() const {
			return *message;
		}

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
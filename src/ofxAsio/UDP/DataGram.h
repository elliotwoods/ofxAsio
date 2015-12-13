#pragma once

#include "../Includes.h"
#include "EndPoint.h"

#include <string>

namespace ofxAsio {
	namespace UDP {
		class DataGram {
		public:
			DataGram();
			~DataGram();

			void setMessage(const string &);
			void setMessageExternal(const string &); //uses a pointer to the message string rather than a copy
			string & getMessage();
			const string & getMessage() const;

			void setEndPoint(const EndPoint &);
			EndPoint & getEndPoint();
			const EndPoint & getEndPoint() const;
		protected:
			bool localAllocation;
			std::string * message;

			EndPoint endPoint;
		};
	}
}
#include "DataGram.h"

#include "ofUtils.h"
#include "ofLog.h"

using namespace std;

namespace ofxAsio {
#pragma mark Message
	//----------
	DataGram::Message::~Message() {
		this->clear();
	}

	//----------
	void DataGram::Message::resize(size_t size) {
		if (this->allocation == Allocation::Reference) {
			ofLogWarning("ofxAsio::DataGram::Message") << "You cannot call resize on a message which references external data";
			return;
		}

		if (size == this->_size) {
			//do nothing
			return;
		}

		if (size == 0) {
			this->clear();
		}
		else {
			//create a new buffer with existing data
			auto data = new char[size];
			memcpy(data, this->_data, min<size_t>(size, this->_size));

			//swap this new buffer with the old one
			swap(data, this->_data);
			swap(size, this->_size);

			//delete the old one
			delete[] data;

			//now we're definitely a copy
			this->allocation = Allocation::Copy;
		}
	}

	//----------
	void DataGram::Message::set(const string & message, Allocation allocation) {
		this->set(message.data(), message.size(), allocation);
	}

	//----------
	void DataGram::Message::set(const void * data, size_t size, Allocation allocation) {
		if (size == 0) {
			this->clear();
			return;
		}

		switch (allocation) {
			//theirs is copy
		case Allocation::Copy:
			switch (this->allocation) {
			case Allocation::Copy:
			{
				if (size == this->_size) {
					//special case, no reallocation necessary
					memcpy(this->_data, data, this->_size);
					break;
				}
				//else continue
			}
			case Allocation::Reference:
			case Allocation::Empty:
			{
				this->allocation = Allocation::Copy;
				this->_data = new char[size];
				this->_size = size;

				memcpy(this->_data, data, this->_size);

				break;
			}
			default:
				break;
			}


			//theirs is reference
		case Reference:
			break;


			//theirs isn't valid
		default:
			this->clear();
			break;
		}
	}

	//----------
	void DataGram::Message::clear() {
		switch (this->allocation) {
		case Allocation::Empty:
			return; // do nothing
			break;
		case Allocation::Copy:
			delete[] this->_data;
			break;
		default:
			break;
		}
		this->_data = nullptr;
		this->_size = 0;
		this->allocation = Allocation::Empty;
	}

	//----------
	bool DataGram::Message::empty() const {
		return this->allocation == Allocation::Empty;
	}

	//----------
	const char * DataGram::Message::data() const {
		return this->_data;
	}

	//----------
	char * DataGram::Message::data() {
		return this->_data;
	}

	//----------
	size_t DataGram::Message::size() const {
		return this->_size;
	}

	//----------
	string DataGram::Message::getMessageString() const {
		if (size() == 0) {
			return string();
		}
		else {
			return string((const char *)this->_data, this->_size);
		}
	}

	//----------
	DataGram::Message::Allocation DataGram::Message::getAllocation() const {
		return this->allocation;
	}

#pragma mark DataGram
	//----------
	const DataGram::Message & DataGram::getMessage() const {
		return this->message;
	}

	//----------
	DataGram::Message & DataGram::getMessage() {
		return this->message;
	}
}
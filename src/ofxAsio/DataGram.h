#pragma once

#include "Includes.h"

#include <string>

namespace ofxAsio {
	class DataGram {
	public:
		class Message {
		public:
			enum Allocation {
				Empty = 0,
				Copy,
				Reference
			};

			~Message();

			//local allocation
			void resize(size_t size);

			//set data
			void set(const string &, Allocation allocation = Allocation::Copy);
			void set(const void * data, size_t size, Allocation allocation = Allocation::Copy);
			template<typename PodType>
			void set(const PodType & data, Allocation allocation = Allocation::Copy) {
				static_assert(is_pod<PodType>::value, "ofxAsio::DataGram::set<PodType>(...)  only supports Plain Old Data. For more complex types, you need to serialize your data first.");
				this->set(&data, sizeof(PodType), allocation);
			}
			void clear();

			//get data
			bool empty() const;
			const char * data() const;
			char * data();
			size_t size() const;
			string getMessageString() const;

			Allocation getAllocation() const;
		protected:
			char * _data = nullptr;
			size_t _size = 0;
			Allocation allocation = Allocation::Empty;
		};

		const Message & getMessage() const;
		Message & getMessage();
		
	protected:
		Message message;
	};
}
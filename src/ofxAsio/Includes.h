#pragma once

//comment out this line if you want to use asio with Boost
#define ASIO_STANDALONE
#define ASIO_HAS_STD_ATOMIC
#define ASIO_HAS_STD_TYPE_TRAITS

#include "asio.hpp"

#include "ofUtils.h"

#include <memory>
#include <thread>

using namespace std;
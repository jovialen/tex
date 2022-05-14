#pragma once

#include <stdexcept>

#define TEX_ERROR(msg) throw new std::runtime_error(__FILE__ ":" msg);

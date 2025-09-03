#ifndef FRAME_HPP
#define FRAME_HPP

#include "Page.hpp"
#include "Types.hpp"

struct Frame
{
	Page page{};
	std::uint16_t pin_count = 0;
	bool is_dirty = false; // Added missing is_dirty flag
};

#endif
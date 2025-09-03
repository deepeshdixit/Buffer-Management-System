#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <memory>

using page_id_t = std::uint32_t;
using frame_id_t = std::uint16_t;

// This line should be removed
// constexpr size_t PAGE_SIZE = 512;

class Page;
using RPage = std::shared_ptr<Page>;

#endif
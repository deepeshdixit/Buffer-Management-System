#ifndef PAGE_HPP
#define PAGE_HPP

#include <cstdint>
#include <functional>
#include <vector>

#include "Types.hpp"

// Page size for all pages
constexpr size_t PAGE_SIZE = 4096;

class Page
{
public:
	Page() = default;
	~Page() = default;

	// Accessor to get the page ID
	auto getId() const -> page_id_t { return page_id; }

public:
	// Static members for generating page IDs
	static page_id_t generateId;
	static std::function<page_id_t()> generate_page_id;

	char data[PAGE_SIZE]{};
	page_id_t page_id = 0;
};

#endif
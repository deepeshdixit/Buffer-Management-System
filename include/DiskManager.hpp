#ifndef DISK_MANAGER_HPP
#define DISK_MANAGER_HPP

#include <vector>
#include <map>
#include <optional>
#include <string>

#include "Page.hpp"
#include "Types.hpp"

class DiskManager
{
public:
	// Public constructor
	DiskManager() = default;

	// Public destructor
	~DiskManager() = default;

	auto add_page(const std::string &filename) -> std::optional<std::vector<page_id_t>>;

	auto read_page(page_id_t page_id) -> std::optional<Page>;
	
	auto write_page(page_id_t page_id, const Page& page) -> void;

public:
	// A map to store file handles, from a given filename to a page_id vector
	std::map<std::string, std::vector<page_id_t>> pages;
	size_t num_ios = 0;
};

#endif
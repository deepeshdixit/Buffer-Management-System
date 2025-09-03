#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "DiskManager.hpp"
#include "Page.hpp"

// Auto-generated ID, from Page.cpp
// page_id_t DiskManager::generateId = 0;

auto DiskManager::add_page(const std::string &filename) -> std::optional<std::vector<page_id_t>>
{
    // Return pages if file has already been processed
    if (pages.find(filename) != std::end(pages))
    {
        return pages.at(filename);
    }

    std::ifstream file{filename, std::ios::binary};
    if (!file.is_open())
    {
        return std::nullopt;
    }

    std::vector<page_id_t> page_ids;
    char page_data[PAGE_SIZE];

    while (file.read(page_data, PAGE_SIZE))
    {
        page_id_t new_id = Page::generate_page_id();
        page_ids.emplace_back(new_id);
    }

    file.close();
    
    pages[filename] = page_ids;
    
    return page_ids;
}

auto DiskManager::read_page(page_id_t page_id) -> std::optional<Page>
{
    num_ios++;

    for (const auto& pair : pages)
    {
        // Check if the page_id exists in this file's vector of pages
        for (const auto& stored_page_id : pair.second)
        {
            if (stored_page_id == page_id)
            {
                std::ifstream file{pair.first, std::ios::binary};
                if (!file.is_open())
                {
                    return std::nullopt;
                }
                
                // Calculate the offset based on the page_id
                file.seekg(page_id * PAGE_SIZE);

                Page page{};
                file.read(reinterpret_cast<char*>(&page), PAGE_SIZE);
                file.close();

                return page;
            }
        }
    }
    return std::nullopt;
}

auto DiskManager::write_page(page_id_t page_id, const Page& page) -> void
{
    num_ios++;
    // Write back to the correct file, not fully implemented for simplicity
    for (const auto& pair : pages)
    {
        // Check if the page_id exists in this file's vector of pages
        for (const auto& stored_page_id : pair.second)
        {
            if (stored_page_id == page_id)
            {
                std::fstream file{pair.first, std::ios::binary | std::ios::in | std::ios::out};
                if (!file.is_open())
                {
                    // Error handling or simple return
                    return;
                }
                file.seekp(page_id * PAGE_SIZE);
                file.write(reinterpret_cast<const char*>(&page), PAGE_SIZE);
                file.close();
                return;
            }
        }
    }
}
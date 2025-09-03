#ifndef BUFFER_POOL_MANAGER_HPP
#define BUFFER_POOL_MANAGER_HPP

#include <array>
#include <map>
#include <optional>
#include <list>
#include <vector>

#include "DiskManager.hpp"
#include "Frame.hpp"
#include "Replacer.hpp"
#include "Types.hpp"

// Define a simple FreeList for managing free frames
template <size_t N>
class FreeList
{
public:
    FreeList() {
        for(size_t i = 0; i < N; ++i) {
            frames.push_back(i);
        }
    }

    auto push(frame_id_t frame_id) {
        frames.push_back(frame_id);
    }

    auto pop() -> frame_id_t {
        auto frame_id = frames.front();
        frames.pop_front();
        return frame_id;
    }

    auto size() -> size_t {
        return frames.size();
    }

private:
    std::list<frame_id_t> frames;
};

// Type aliases for pointers to the DiskManager and Replacer classes
using PDiskManager = DiskManager*;

template <size_t N>
using PReplacer = Replacer<N>*;

// Main BufferPoolManager class
template <size_t N>
class BufferPoolManager
{
public:
    BufferPoolManager(PDiskManager _disk_manager, PReplacer<N> _replacer);

    ~BufferPoolManager();

    auto fetch_page(page_id_t page_id) -> std::optional<Page>;

    auto unpin_page(page_id_t page_id) -> bool;
    
    auto flush_page(page_id_t page_id) -> void;

private:
    // Page table for quick lookups from page_id to frame_id
    std::map<page_id_t, frame_id_t> page_table;

    // The frames in the buffer pool
    std::array<Frame, N> frames;

    // Free list for available frames
    FreeList<N> free_list;

    // Pointer to the disk manager for I/O operations
    PDiskManager disk_manager;

    // Pointer to the replacer for page eviction
    PReplacer<N> replacer;
};

#include "BufferPoolManager.inl"

#endif
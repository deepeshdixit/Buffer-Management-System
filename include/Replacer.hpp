#ifndef REPLACER_HPP
#define REPLACER_HPP

#include "Frame.hpp"
#include "Types.hpp"

template <size_t N>
class Replacer
{
public:
    // Virtual destructor for proper inheritance
    virtual ~Replacer() = default;

    // Pin a frame so it cannot be a victim
    virtual auto pin(frame_id_t frame_id) -> void = 0;

    // Unpin a frame so it can be a victim
    virtual auto unpin(frame_id_t frame_id) -> void = 0;

    // Select a victim frame to be replaced
    virtual auto victim() -> std::optional<frame_id_t> = 0;

    // Provide the replacer with access to the frames array
    void set_frames(std::array<Frame, N>* frames) {
        this->frames = frames;
    }

protected:
    std::array<Frame, N>* frames;
};

#endif
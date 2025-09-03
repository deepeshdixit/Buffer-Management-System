#ifndef CLOCK_REPLACER_HPP
#define CLOCK_REPLACER_HPP

#include <vector>
#include <optional>
#include "Replacer.hpp"

template <size_t N>
class ClockReplacer : public Replacer<N>
{
public:
    ClockReplacer() : clock_hand(0), occupied_frames(0) {
        clock_state.resize(N, {false, false});
    }

    virtual ~ClockReplacer() = default;

    auto pin(frame_id_t frame_id) -> void override;
    auto unpin(frame_id_t frame_id) -> void override;
    auto victim() -> std::optional<frame_id_t> override;

private:
    std::vector<std::pair<bool, bool>> clock_state; // <is_pinned, is_referenced>
    size_t clock_hand;
    size_t occupied_frames;
};

#include "ClockReplacer.inl"

#endif
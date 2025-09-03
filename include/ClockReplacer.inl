#include <stdexcept>

template <size_t N>
auto ClockReplacer<N>::pin(frame_id_t frame_id) -> void
{
    if (frame_id >= N) {
        throw std::out_of_range("Frame ID out of range in pin.");
    }
    clock_state[frame_id].first = true; // Set is_pinned to true
    clock_state[frame_id].second = false; // Reset reference bit
}

template <size_t N>
auto ClockReplacer<N>::unpin(frame_id_t frame_id) -> void
{
    if (frame_id >= N) {
        throw std::out_of_range("Frame ID out of range in unpin.");
    }
    if (clock_state[frame_id].first) { // Check if frame was pinned
        clock_state[frame_id].first = false; // Set is_pinned to false
    }
}

template <size_t N>
auto ClockReplacer<N>::victim() -> std::optional<frame_id_t>
{
    for (size_t i = 0; i < 2 * N; ++i) { // Loop twice through the buffer
        if (!clock_state[clock_hand].first) { // If not pinned
            if (clock_state[clock_hand].second) { // If referenced
                clock_state[clock_hand].second = false; // Reset reference bit
            } else { // If not referenced
                auto victim_id = clock_hand;
                clock_hand = (clock_hand + 1) % N;
                return victim_id;
            }
        }
        clock_hand = (clock_hand + 1) % N;
    }
    return std::nullopt; // No unpinned frame found
}
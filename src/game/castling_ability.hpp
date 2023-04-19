#pragma once

#include <bitset>
#include <cassert>
#include <initializer_list>

namespace chess {

enum class CastlingRight {
    none = -1,
    white_king = 0,
    white_queen,
    black_king,
    black_queen
};

class CastlingAbility {
public:
    CastlingAbility() { }
    explicit CastlingAbility(const std::initializer_list<CastlingRight> list)
    {
        for (const auto castling_right : list)
            set(castling_right);
    }

    void set(const CastlingRight castling_right)
    {
        assert(castling_right != CastlingRight::none);
        mask_.set(static_cast<std::size_t>(castling_right));
    }

    bool has(const CastlingRight castling_right) const
    {
        assert(castling_right != CastlingRight::none);
        return mask_.test(static_cast<std::size_t>(castling_right));
    }

    bool operator==(const CastlingAbility& other) const = default;
    bool operator!=(const CastlingAbility& other) const = default;

private:
    std::bitset<4> mask_;
};

}  // namespace chess

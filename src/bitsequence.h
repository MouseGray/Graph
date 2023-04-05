#pragma once

#include <cstdint>
#include <memory>

class BitSqeuence
{
public:
    BitSqeuence(std::size_t size) :
        size_{size}, data_{std::make_unique<uint64_t[]>(InternalSize(size))}
    {

    }

    __attribute__((__always_inline__))
    void Set(std::size_t n) noexcept
    {
        data_.get()[n >> 6] |= 1 << (n & 0x3F);
    }

    __attribute__((__always_inline__))
    bool Test(std::size_t n) const noexcept
    {
        return data_.get()[n >> 6] & (1 << (n & 0x3F));
    }

    __attribute__((__always_inline__))
    bool IsAll() const noexcept
    {
        std::size_t count = 0;

        for(std::size_t i = 0; i < InternalSize(size_); ++i)
            count += __builtin_popcountll(data_.get()[i]);

        return count == size_;
    }
private:
    __attribute__((__always_inline__, __const__))
    static std::size_t InternalSize(std::size_t size) noexcept
    {
        return (size >> 6) + !!(size & 0x3F);
    }

    std::size_t                 size_;
    std::unique_ptr<uint64_t[]> data_;
};

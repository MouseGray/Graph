#pragma once

#include <cstdint>
#include <cstring>

#include "utils.h"

struct Edge{ uint16_t A, B; uint16_t Length; };

class Edges
{
    struct Edge { uint16_t& A, &B; };
    struct ConstEdge { const uint16_t& A, &B; };
public:
    Edges(std::size_t size) noexcept :
        size_{size}
    {
        auto internal_size = InternalSize(size);

        as_.reset((uint16_t*)_mm_malloc(internal_size, 32));
        bs_.reset((uint16_t*)_mm_malloc(internal_size, 32));

        std::memset(as_.get(), 0xFF, internal_size);
        std::memset(bs_.get(), 0xFF, internal_size);
    }

    inline Edge operator[](std::size_t n) noexcept
    {
        return { as_.get()[n], bs_.get()[n] };
    }

    inline ConstEdge operator[](std::size_t n) const noexcept
    {
        return { as_.get()[n], bs_.get()[n] };
    }

    __attribute__((__always_inline__, __const__))
    std::size_t Size() const noexcept
    {
        return size_;
    }
private:
    __attribute__((__always_inline__, __const__))
    static std::size_t InternalSize(std::size_t size) noexcept
    {
        return ((size >> 4) + !!(size & 0x0F)) << 5;
    }

    std::size_t     size_;
    aligned_pointer as_;
    aligned_pointer bs_;
};

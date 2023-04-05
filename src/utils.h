#pragma once

#include <cstdint>
#include <memory>

#include <immintrin.h>

struct mm_free
{
    void operator()(void* ptr) const noexcept
    {
        _mm_free(ptr);
    }
};

using aligned_pointer = std::unique_ptr<uint16_t, mm_free>;

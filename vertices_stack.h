#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>

#include <immintrin.h>

template<std::size_t S>
class VerticesStack
{
    static_assert((S & 0xF) == 0, "invalid stack size");
public:
    VerticesStack() noexcept :
        size_{}
    {
        std::fill(data_, data_ + S, 0xFFFF);
    }

    template<typename ...Args>
    inline void Push(std::size_t pos, Args ...vertices) noexcept
    {
        assert(size_ < S);

        (PushImpl(pos, vertices), ...);

        if(pos < size_)
            std::fill(data_ + pos, data_ + size_, 0xFFFF);

        size_ = pos;
    }

    inline void Pop(std::size_t pos)
    {
        if(pos < size_)
            std::fill(data_ + pos, data_ + size_, 0xFFFF);

        size_ = pos;
    }

    inline bool IsContain(uint16_t vertex) noexcept
    {
        constexpr auto it_count = S >> 4;

        __m256i vertex_vector = _mm256_set1_epi16(vertex);

        for(std::size_t it = 0; it < it_count; ++it)
        {
            __m256i vertices_vector = _mm256_load_si256((__m256i*)(data_ + (it << 4)));

            __m256i result = _mm256_cmpeq_epi16(vertex_vector, vertices_vector);

            int result_mask = _mm256_movemask_epi8(result);

            if(result_mask)
                return true;
        }
        return false;
    }

    inline std::size_t MaxSize() const noexcept
    {
        return S;
    }
private:
    inline void PushImpl(std::size_t& pos, uint16_t vertex) noexcept
    {
        data_[pos++] = vertex;
    }

    std::size_t size_;
    uint16_t    data_[S] __attribute__((aligned(32)));
};

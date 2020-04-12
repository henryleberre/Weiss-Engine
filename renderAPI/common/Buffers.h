#pragma once

#include "../../common/Include.h"

class VertexBufferData {
protected:
	std::vector<int8_t> m_vertexData;

public:
    inline void Set(const void* buff, const size_t bufferSize) noexcept
    {
        std::memcpy(this->m_vertexData.data(), buff, bufferSize);
    }

    template <typename CONTAINER>
    inline void Set(const CONTAINER& container) noexcept
    {
        this->Set(container.data(), container.size() * sizeof(container[0])); 
    }

    template <typename T>
    inline T& GetVertex(const size_t vertexIndex) noexcept
    {
        return *(static_cast<T*>(this->m_vertexData.data()) + vertexIndex);
    }

    template <typename T>
    inline void SetVertex(const size_t vertexIndex, const T& vertex) noexcept
    {
        this->GetVertex(vertexIndex) = vertex;
    }
};

class IndexBufferData {
protected:
	std::vector<uint32_t> m_indexData;

public:
    inline void Set(const void* buff, const size_t nIndices) noexcept
    {
        std::memcpy(this->m_indexData.data(), buff, nIndices * sizeof(uint32_t));
    }

    template <typename CONTAINER>
    inline void Set(const CONTAINER& container) noexcept
    {
        this->Set(container.data(), container.size());
    }

    inline uint32_t& GetIndex(const size_t indexIndex) noexcept
    {
        return this->m_indexData[indexIndex];
    }

    inline void SetIndex(const size_t indexIndex, const uint32_t index) noexcept
    {
        this->GetIndex(indexIndex) = index;
    }
};

class ConstantBufferData {
protected:
    std::vector<int8_t> m_constantBufferData;

public:
    template <typename T>
    inline T& Get()
    {
        return *((T*)this->m_constantBufferData.data());
    }

    template <typename T>
    inline void Set(const T& obj)
    {
        this->Get<T>() = obj;
    }
};
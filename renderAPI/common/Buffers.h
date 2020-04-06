#pragma once

#include "../../common/Include.h"

class VertexBuffer {
public:
    virtual size_t GetCount() = 0;
    virtual void   SetData(const void* buff, const size_t nVertices) = 0;

public:
    template <typename CONTAINER>
    void SetData(const CONTAINER& container)
    {
        this->SetData(container.data(), container.size());
    }
};

class IndexBuffer {
public:
    virtual size_t GetCount() = 0;
    virtual void   SetData(const uint32_t* buff, const size_t nIndices) = 0;

public:
    template <typename CONTAINER>
    void SetData(const CONTAINER& container)
    {
        this->SetData(container.data(), container.size());
    }
};

class ConstantBuffer {
public:
    virtual void SetData(const void* buff, const size_t bufferSize) = 0;
};
template<typename T, size_t N>
class Array
{
public:
    Array()
        : m_Data{}
    {}

    size_t size() const
    {
        return N;
    }

    T& operator[](size_t i)
    {
        assert(i < N);

        return m_Data[i];
    }

    const T& operator[](size_t i) const
    {
        assert(i < N);

        return m_Data[i];
    }

private:
    T m_Data[N];
};

template<>
class Array<float, 4>
{
public:
    Array()
    : m_Vec(_mm_setzero_ps())
    {}

    size_t size() const
    {
        return 4;
    }

    float& operator[](size_t i)
    {
        assert(i < 4);
        return m_Data[i];
    }

    const float& operator[](size_t i) const
    {
        assert(i < 4);
        return m_Data[i];
    }

private:
    union
    {
        __m128 m_Vec;     // Vectorized data.
        float  m_Data[4]; // Float data.
    };
};

template<typename T, size_t N>
class Array<T*, N>
{
public:
    explicit Array(T* data)
        : m_Data(data)
    {}

    T& operator[](size_t i)
    {
        assert(i < N);
        return m_Data[i];
    }

    const T& operator[](size_t i) const
    {
        assert(i < N);
        return m_Data[i];
    }

private:
    T* m_Data;
};

// Specialized for arrays of size 4 and arbitrary type.
template<typename T>
class Array<T, 4>
{
    //...
};

// Specialized for float arrays of arbitrary size.
template<size_t N>
class Array<float, N>
{
    //...
};

extern template Array<float, 2>; // Explicit template instantiation declaration.
extern template Array<float, 3>; // Explicit template instantiation declaration.
extern template Array<float, 4>; // Explicit template instantiation declaration.
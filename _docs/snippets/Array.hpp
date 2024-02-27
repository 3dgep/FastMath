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

extern template Array<float, 2>; // Explicit template instantiation declaration.
extern template Array<float, 3>; // Explicit template instantiation declaration.
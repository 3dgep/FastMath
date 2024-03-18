template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Object
{
public:
    Object(int i, float f, int* ip, double d)
    : m_i(i)
    , m_f(f)
    , mp_i(ip)
    , m_d(d)
    {}

private:
    int m_i;
    float m_f;
    int* mp_i;
    double m_d;
};

std::unique_ptr<Object> make_unique(int args0, float args1, int* args2, double args3)
{
    return std::unique_ptr<Object>(new Object(std::forward<int>(args0), std::forward<float>(args1), std::forward<int*>(args2), std::forward<double>(args3)));
}
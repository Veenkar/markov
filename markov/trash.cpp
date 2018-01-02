template<typename T, size_t N>
class Multi
{
private:
    int8_t cmp(const Multi& rhs, size_t from=0)
    {
        if (from >= N)
        {
            return 0;
        }

        if (data[from] > rhs[from])
        {
            return 1;
        }
        else if (data[from] < rhs[from])
        {
            return -1;
        }
        else
        {
            return cmp(rhs, from + 1);
        }
    }

public:
    Multi(std::initializer_list<T> init)
    {
        std::copy(init.begin(), init.begin()+MIN(N, init.size()), data.begin());
    }

    std::array<T, N> data;
    bool operator< (const Multi& rhs)
    {
        cmp(rhs) > 0;
    }
};

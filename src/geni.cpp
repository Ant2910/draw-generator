#include <iostream>

template <typename T,bool ORDER = true,bool REPETITION = true>
class GenericUrn
{   
    public:
        class It
        {
            public:
                It(T a);

                It operator++();

            private:
                T m_a;
        };
    public:
        GenericUrn(T i);

        enum class Stat
        {
            a,
            b,
            c
        };

        T output() const;

    private:
        T m_i;
        bool O = ORDER;
        bool R = REPETITION;
};

template<typename T, bool ORDER, bool REP>
class Test
{
    public:
        class It
        {
            public:
                using difference_type = std::ptrdiff_t;


                It operator+(const difference_type& n) const
                { 
                    auto temp {*this};
                    return (temp += n);
                }

                template<typename T1, bool O, bool R>
                friend operator+(const difference_type& n, const It& other)
                {
                    return other + n;
                }

        }
};

//Teil mir den code in header und implementations file


#if __has_include("gen.cpp")
#include "gen.cpp"
#endif //__has_include

int main()
{
    GenericUrn<int,true,true> u {1};

    std::cout << u.output() << std::endl;

    return 0;
}

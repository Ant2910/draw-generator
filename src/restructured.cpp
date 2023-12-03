#include <vector>
#include <iostream>
#include <exception> 
#include <algorithm>
#include <cmath>
#include <iterator>
#include <type_traits>
#include <concepts>
#include <limits>
using namespace std;

using uint = unsigned int; 
using Draw = std::vector<uint>;
/*
template<class T> 
concept R = std::ranges::range<T>;

template<class T> 
concept IR = std::ranges::input_range<T>;

template<class T>
concept FR = std::ranges::forward_range<T>;

template<class T>
concept BR = std::ranges::bidirectional_range<T>;

template<class T>
concept RR = std::ranges::random_access_range<T>;
*/
string to_string(const Draw& draw)
{   
    string stdraw {};
    for(uint posCount{}; posCount < draw.size(); ++posCount)
    {
        stdraw += to_string(draw.at(posCount));
        if(posCount != (draw.size()-1))
        {
            stdraw += " ";
        }
    }
    return stdraw;
}

int factorial(const int& n)
{
    if(n == 0)
    {
        return 1;
    }
    return n*factorial(n-1);
}

//UrnOR
class UrnOR
{   
    public:
    class Iterator
    {   
        public:
            using iterator_category = std::random_access_iterator_tag;  //std::bidirectional_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = Draw; //vector<unsigned int>
            using pointer           = Draw*;  
            using reference         = const Draw; //Kommentar anmerken
            using size_type         = std::size_t;  //https://en.cppreference.com/w/cpp/types/size_t

            //Iterators: constructible, copy-constructible, copy-assignable, destructible and swappable
            enum class Status
            {
                invalidFront,
                valid,
                invalidBack
            };
            
            Iterator(const UrnOR* urn, const uint& ordinalnumber, const Status& status): m_urn{ urn },
                                                                                         m_ordinalnumber{ static_cast<int>(ordinalnumber) },
                                                                                         m_status { status }{}

            Iterator() = default;   //Für ranges::random_access_iterator

            string status() const
            {
                switch(m_status)
                {
                    case Status::invalidFront: return "invalidFront"; break;
                    case Status::valid: return "valid"; break;
                    case Status::invalidBack: return "invalidBack"; break;
                    default: throw std::invalid_argument("m_status is invalid."); break;
                }
            }

            uint n() const
            {
                return (*m_urn).n();
            }

            uint k() const
            {
                return (*m_urn).k();
            }

            uint z() const
            {
                return (*m_urn).z();
            }

            int ordinalnumber() const
            {
                return m_ordinalnumber;
            }

            const value_type operator*() const 
            {   
                if(m_ordinalnumber >= z() || m_ordinalnumber < 0)
                {
                    return Draw((k()), 0);
                }
                return (*m_urn).draw(m_ordinalnumber);
            }

            Iterator& operator++()
            {   
                ++m_ordinalnumber;
                
                if(m_ordinalnumber == 0)
                {  
                    m_status = Status::valid;
                }
                else if(m_ordinalnumber < 0)
                {
                    m_status = Status::invalidFront;
                }
                else if(m_ordinalnumber >= z())
                {
                    m_status = Status::invalidBack;
                }
                
                return *this;
            }
                
            Iterator operator++(int)
            { 
                auto temp {*this};
                ++(*this);
                return temp;
            }
            
            Iterator& operator--()
            {   
                --m_ordinalnumber;
                if(m_ordinalnumber == z()-1)
                {  
                    m_status = Status::valid;
                }
                else if(m_ordinalnumber < 0)
                {
                    m_status = Status::invalidFront;
                }
                else if(m_ordinalnumber >= z())
                {
                    m_status = Status::invalidBack;
                }
                return *this;
            }
            
            Iterator operator--(int)
            {
                auto temp {*this};
                --(*this);
                return temp;
            }
            
            bool operator== (const Iterator& other) const
            { 
                return (m_ordinalnumber == other.m_ordinalnumber);
            }   

            bool operator!= (const Iterator& other) const
            {  
                return !(*this == other); 
            }

            bool operator< (const Iterator& other) const
            { 
                return (m_ordinalnumber < other.m_ordinalnumber);
            }

            bool operator> (const Iterator& other) const 
            { 
                return (m_ordinalnumber > other.m_ordinalnumber);
            }

            bool operator<=(const Iterator& other) const
            { 
                return (*this == other || *this < other);
            }

            bool operator>=(const Iterator& other) const
            { 
                return (*this == other || *this > other);
            }

            //Addition mit += (bei allen additionen und subtraktionen Klammerausdrücke testen in catch2)
            Iterator& operator+=(const difference_type& other)
            {   
                if(other >= 0)
                {
                    for(uint incCount{}; incCount < other; ++incCount)
                    {
                        ++(*this);
                    }
                }
                else if(other < 0)
                {   
                    long int positivOther {other * -1};
                    for(uint decCount{}; decCount < positivOther; ++decCount)
                    {
                        --(*this);
                    }
                }
                return *this;
            }

            //Addition mit +
            Iterator operator+(const difference_type& n) const //ist besser ohne const
            { 
                auto temp {*this};
                return (temp += n);
            }
            
            friend Iterator operator+(const difference_type& n, const Iterator& other) 
            {
                return other + n;
            }
            
            //Subtraktion mit -=
            Iterator& operator-=(const difference_type& n)
            {
                long int negativ {n * -1};
                (*this) += negativ;
                return *this;
            }

            //Subtraktion mit -
            Iterator operator-(const difference_type& n) const
            { 
                auto temp {*this};
                return (temp -= n);
            }

            //Difference
            difference_type operator-(const Iterator& other) const
            { 
                return m_ordinalnumber - other.m_ordinalnumber;
            }

            //Index
            //it[0] = {2,2}; ist nicht möglich da reference = const Draw und so kann der Wert nicht verändert werden
            //Sollte aber kein Problem sein, da es für die Urn nicht möglich sein sollte
            reference operator[](size_type index) const 
            { 
                if(index >= z() || index < 0)
                {
                    return Draw((k()), 0);
                }
                return (*m_urn).draw(index);
            }

            ~Iterator() = default;

        protected:
            const UrnOR* m_urn;
            int m_ordinalnumber;
            Status m_status;
    };

    public:
        explicit UrnOR(uint n,uint k,uint check = 1):m_n { n },
                                                     m_k { k }
                                                     /*m_z { static_cast<uint>(pow(n,k)) }*/
        {   
            if (check == 1 && m_n == 0 && m_k > 0)
            {
                throw std::domain_error("UrnOR with n == 0 and k > 0 is not valid.");
            }
            
        }

        uint n() const
        {
            return m_n;
        }

        uint k() const
        {
            return m_k;
        }

        virtual uint z() const
        {   
            if(m_k == 0)
            {
                return 0; //vielleicht auch mit im Konstruktor verbieten?
            }
            return static_cast<uint>(pow(m_n,m_k));
        }

        Iterator begin()
        {
            return Iterator(this,0,Iterator::Status::valid);
        }

        Iterator end()
        {
            return Iterator(this,z(),Iterator::Status::invalidBack);
        }

        auto rbegin()
        {   
            return make_reverse_iterator(end());
        }

        auto rend()
        {
           return make_reverse_iterator(begin());
        }

        [[nodiscard]] bool valid(const Draw& draw) const
        {   
            if(m_k == draw.size())
            {
                for(uint posCount {}; posCount < m_k; ++posCount)
                {   
                    if(!(draw.at(posCount) <= (m_n-1)))
                    {   
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        
        virtual Draw nextDraw(Draw draw) const
        {   
            if(valid(draw))
            {        
                for (uint downCount { m_k }; downCount > 0; --downCount)
                {
                    if (draw[downCount - 1] < m_n - 1)
                    {   
                        ++draw[downCount - 1];
                        for (uint upCount { downCount }; upCount < m_k; ++upCount)
                        {
                            draw[upCount] = 0;
                        }
                        return draw;
                    }
                }
            }
            throw std::overflow_error("There is no valid next draw.");
        }
        
        virtual Draw backDraw(Draw draw) const
        {   
            if(valid(draw) && draw != Draw(m_k,0))
            {
                for(uint downCount {m_k}; downCount > 0; --downCount)
                {
                    if(draw[downCount-1] != 0)
                    {
                        draw[downCount-1] -= 1;
                        return draw;
                    }
                    else
                    {
                        draw[downCount-1] = m_n-1;
                    }
                }
                return draw;
            }
            throw std::underflow_error("There is no valid back draw.");
        }

        virtual Draw draw(uint ordinalnumber) const
        {   
            Draw draw(m_k, 0);
            for (int posCount {static_cast<int>(m_k - 1)}; posCount >= 0; --posCount)
            {
                for (uint timesCount {m_n - 1}; timesCount >= 1; --timesCount)
                {
                    if (static_cast<uint>(pow(m_n, posCount)) * timesCount <= ordinalnumber)
                    {
                        draw[posCount] = timesCount;
                        ordinalnumber -= static_cast<uint>(pow(m_n, posCount)) * timesCount;
                        break;
                    }
                }
            }
            reverse(draw.begin(), draw.end());
            return draw;
        }

        virtual Draw firstDraw() const
        {
            return Draw(m_k,0);
        }

        virtual Draw lastDraw() const
        {
            return Draw(m_k,m_n-1);
        }

        virtual ~UrnOR() = default;
         
    protected:
        const uint m_n,
                   m_k;
                   //m_z;
};

//UrnO
class UrnO: public virtual UrnOR
{
    public:
        explicit UrnO(uint n,uint k,uint check = 2): UrnOR { n,k,check }
        {   
            if (check == 2 && m_k > m_n)
            {
                throw std::domain_error("UrnO with k > n is not valid.");
            }
        }

        virtual uint z() const
        {
            return (factorial(m_n)/factorial(m_n-m_k));
        }

        //Funktioniert aber vielleicht noch verbesserung?
        virtual Draw draw(uint ordinalnumber) const
        {   
            if(ordinalnumber >= z())
            {
                throw std::overflow_error("There is no valid next draw.");
            }

            Draw result {};
            int repCount {-1};
            for(uint upCount {}; upCount < UrnOR::z(); ++upCount)
            {   
                result = UrnOR::draw(upCount);
                if(!repetitions(result))
                {   
                    ++repCount;
                    if(repCount == ordinalnumber)
                    {
                        break;
                    }
                }
            }
            return result;
        }

        bool repetitions(const Draw& repDraw) const
        {
            for (uint outerCount {}; outerCount < m_k - 1; ++outerCount)
            {
                for (uint innerCount { outerCount + 1}; innerCount < m_k; ++innerCount)
                {
                    if (repDraw[outerCount] == repDraw[innerCount])
                    {
                        return true;
                    }
                }
            }
        return false;
    }
};


int main()
{   
    UrnO urn {3,3};
    cout << to_string(urn.draw(0)) << endl;
    cout << to_string(urn.draw(1)) << endl;
    cout << to_string(urn.draw(2)) << endl;
    cout << to_string(urn.draw(3)) << endl;
    cout << to_string(urn.draw(4)) << endl;
    cout << to_string(urn.draw(5)) << endl;
    //cout << to_string(urn.draw(6)) << endl;
    return 0;
}
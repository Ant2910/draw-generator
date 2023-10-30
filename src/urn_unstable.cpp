#include <vector>
#include <iostream>
#include <exception> 
#include <algorithm>
#include <cmath>
#include <iterator>
#include <type_traits>
#include <concepts>
using namespace std;

using uint = unsigned int;
using Draw = std::vector<uint>;

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

//UrnOR
class UrnOR
{   
    public:
    class Iterator
    {   
        public:
            using iterator_category = std::bidirectional_iterator_tag;//std::forward_iterator_tag; //std::bidirectional_iterator_tag; //erstmal bidirectional und dann später random access wenn möglich
            using difference_type   = std::ptrdiff_t;
            using value_type        = Draw; //vector<unsigned int>
            using pointer           = Draw*;  
            using reference         = const Draw; //Kommentar anmerken

            //Iterators: constructible, copy-constructible, copy-assignable, destructible and swappable
            enum class Status
            {
                begin,
                valid,
                invalid,
                end
            };
            
            Iterator(const UrnOR* urn, const uint& ordinalnumber, const Status& status): m_urn{ urn },
                                                                                         m_ordinalnumber{ ordinalnumber },
                                                                                         m_status { status }{}

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

            uint ordinalnumber() const
            {
                return m_ordinalnumber;
            }

            const value_type operator*() const 
            {   
                if(m_ordinalnumber >= z() || m_ordinalnumber < 0)   //wird nicht kleiner als null da m_ordinalnumber ein uint ist
                {
                    return Draw((k()), 0);
                }
                return (*m_urn).draw(m_ordinalnumber);
            }

            /*const*/ Iterator operator++() //Iterator&
            {   
                if (m_status == Status::begin)
                {
                    m_status = Status::valid;
                    m_ordinalnumber = 0;
                }
                else if(m_status != Status::end)
                {
                    ++m_ordinalnumber;
                    m_status = Status::valid;
                }
                if(m_ordinalnumber == z())//(m_ordinalnumber >= z())
                {
                    m_status = Status::end;
                }
                else if(m_ordinalnumber > z())
                {
                    m_status = Status::invalid;
                }
                return *this;
            }
                
            /*const*/ Iterator operator++(int)
            { 
                auto temp {*this};
                ++(*this);
                return temp;
            }
            
            /*const*/ Iterator operator--() //Iterator&
            {   
                if(m_status == Status::end)
                {
                    m_status = Status::valid;
                    m_ordinalnumber = m_urn->z() - 1;
                }
                else if(m_status != Status::begin)
                {   
                    --m_ordinalnumber;
                    m_status = Status::valid;
                }
                /*
                if(m_ordinalnumber < 0) //wird nicht kleiner als null da m_ordinalnumber ein uint ist
                {                       //wird auf uint max 4294967295 gesetzt
                    m_status = Status::begin;
                }
                */
                if(m_ordinalnumber > z())
                {
                    m_status = Status::invalid;
                }
                return *this;
            }
            
            /*const*/ Iterator operator--(int)
            {
                auto temp {*this};
                --(*this);
                return temp;
            }
            
            friend bool operator== (const Iterator& a, const Iterator& b) 
            { 
                return (a.m_ordinalnumber == b.m_ordinalnumber) || 
                    (a.m_status == Status::end && b.m_status == Status::end) ||
                    (a.m_status == Status::begin && b.m_status == Status::begin);
            }   

            friend bool operator!= (const Iterator& a, const Iterator& b)
            {  
                return !(a == b); 
            }

            //Addition mit += (bei allen additionen und subtraktionen Klammerausdrücke testen in catch2)
            /*const*/ Iterator& operator+=(const difference_type& other)
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
            Iterator operator+(const difference_type& other) const //ist besser ohne const
            { 
                auto temp {*this};
                return (temp += other);
            }

            //Subtraktion mit -=
            /*const*/ Iterator& operator-=(const difference_type& other)
            {
                long int negativOther {other * -1};
                (*this) += negativOther;
                return *this;
            }

            //Subtraktion mit -
            Iterator operator-(const difference_type& other) const
            { 
                auto temp {*this};
                return (temp -= other);
            }

            //Difference
            //Funktioniert noch nicht ganz richtig für rbegin - rend wegen uint max
            difference_type operator-(const Iterator& other)
            { 
                return m_ordinalnumber - other.m_ordinalnumber;
            }

            ~Iterator() = default;

        protected:
            const UrnOR* m_urn;
            uint m_ordinalnumber;
            Status m_status;
    };

    public:
        explicit UrnOR(uint n,uint k,uint check = 1):m_n { n },
                                                     m_k { k },
                                                     m_z { static_cast<uint>(pow(n,k)) }
        {
            if (check == 1 && m_n == 0 && m_k > 0)
            {
                throw std::domain_error(
                    "UrnOR with n == 0 and k > 0 is not valid.");
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

        uint z() const
        {
            return m_z;
        }

        Iterator begin()
        {
            return Iterator(this,0,Iterator::Status::valid);
        }

        Iterator end()
        {
            return Iterator(this,m_z,Iterator::Status::end);
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
            if (!(ordinalnumber < m_z))
            {
                throw std::overflow_error("There is no valid draw.");
            }

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
                   m_k,
                   m_z;
   };

int main()
{   
    UrnOR urn {2,2};

    cout << "+= und -=" << endl;
    auto it {urn.begin()};
    cout << to_string(*it) << endl;
    it += 2;
    cout << to_string(*it) << endl;
    it -= 1;
    cout << to_string(*it) << endl;
    it -= 0;
    cout << to_string(*it) << endl;

    cout << "+ und -" << endl;
    auto it1 {urn.begin()};
    cout << to_string(*it1) << endl;
    it1 = it1 + 2;
    cout << to_string(*it1) << endl;
    it1 = it1 - 1;
    cout << to_string(*it1) << endl;
    it1 = it1 - 0;
    cout << to_string(*it1) << endl;

    /*
    auto it {urn.begin()};

    cout << to_string(*--it) << endl;
    cout << it.ordinalnumber() << endl;
    cout << to_string(*--it) << endl;
    cout << it.ordinalnumber() << endl;

    while(it != urn.end())
    {
        cout << to_string(*it) << endl;
        ++it;
    }

    auto it1 {urn.end()};
    auto it2 {urn.end()};
    cout << "--it" << endl;
    cout << to_string(*--it1) << endl;
    cout << to_string(*--it1) << endl;
    cout << to_string(*--it1) << endl;
    cout << "it--" << endl;
    cout << to_string(*it2--) << endl;
    cout << to_string(*it2--) << endl;
    cout << to_string(*it2--) << endl;

    auto it3 {urn.begin()};
    auto it4 {urn.begin()};
    cout << "++it" << endl;
    cout << to_string(*++it3) << endl;
    cout << to_string(*++it3) << endl;
    cout << to_string(*++it3) << endl;
    cout << "it++" << endl;
    cout << to_string(*it4++) << endl;
    cout << to_string(*it4++) << endl;
    cout << to_string(*it4++) << endl;

    cout << "Loop begin -> end mit ++it" << endl;
    for(auto it {urn.begin()}; it != urn.end(); ++it)
    {
        cout << to_string(*it) << endl;
    }

    cout << "Loop end -> begin mit --it" << endl;
    for(auto itb {urn.end()}; itb != urn.begin(); --itb)
    {
        cout << to_string(*itb) << endl;
    } 
    
    cout << "Loop begin -> end mit it++" << endl;
    for(auto it {urn.begin()}; it != urn.end(); it++)
    {
        cout << to_string(*it) << endl;
    }

    cout << "Loop end -> begin mit it--" << endl;
    for(auto itb {urn.end()}; itb != urn.begin(); itb--)
    {
        cout << to_string(*itb) << endl;
    }

    auto itbr1 {urn.rbegin()};
    auto itbr2 {urn.rbegin()};

    cout << "++it" << endl;
    cout << to_string(*++itbr1) << endl;
    cout << to_string(*++itbr1) << endl;
    cout << to_string(*++itbr1) << endl;
    cout << "it++" << endl;
    cout << to_string(*itbr2++) << endl;
    cout << to_string(*itbr2++) << endl;
    cout << to_string(*itbr2++) << endl;

    auto itre1 {urn.rend()};
    auto itre2 {urn.rend()};

    cout << "--it" << endl;
    cout << to_string(*--itre1) << endl;
    cout << to_string(*--itre1) << endl;
    cout << to_string(*--itre1) << endl;
    cout << "it--" << endl;
    cout << to_string(*itre2--) << endl;
    cout << to_string(*itre2--) << endl;
    cout << to_string(*itre2--) << endl;

    cout << "Loop rbegin -> rend mit ++it" << endl;
    for(auto it {urn.rbegin()}; it != urn.rend(); ++it)
    {
        cout << to_string(*it) << endl;
    }

    cout << "Loop rend -> rbegin mit --it" << endl;
    for(auto itb {urn.rend()}; itb != urn.rbegin(); --itb)
    {
        cout << to_string(*itb) << endl;
    }
    */
    return 0;
}
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

//using uint = int; //unsigned int
using Draw = std::vector<int>;

string to_string(const Draw& draw)
{   
    string stdraw {};
    for(int posCount{}; posCount < draw.size(); ++posCount)
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
            
            Iterator(const UrnOR* urn, const int& ordinalnumber, const Status& status): m_urn{ urn },
                                                                                         m_ordinalnumber{ ordinalnumber },
                                                                                         m_status { status }{}
            
            int n() const
            {
                return (*m_urn).n();
            }

            int k() const
            {
                return (*m_urn).k();
            }

            int z() const
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

            /*const*/ Iterator operator++() //Iterator&
            {   
                if (m_status == Status::invalidFront)
                {
                    m_status = Status::valid;
                    m_ordinalnumber = 0;
                }
                else if(m_status != Status::invalidBack)
                {
                    ++m_ordinalnumber;
                    m_status = Status::valid;
                }
                if(m_ordinalnumber >= z())
                {
                    m_status = Status::invalidBack;
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
                if(m_status == Status::invalidBack)
                {
                    m_status = Status::valid;
                    m_ordinalnumber = z() - 1;    //m_urn->z() - 1;   //Warum nicht z() - 1?
                }
                else if(m_status != Status::invalidFront)
                {   
                    --m_ordinalnumber;
                    m_status = Status::valid;
                }
                if(m_ordinalnumber < 0)
                {                     
                    m_status = Status::invalidFront;
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
                return (a.m_ordinalnumber == b.m_ordinalnumber);
                    //(a.m_status == Status::end && b.m_status == Status::end) ||
                    //(a.m_status == Status::begin && b.m_status == Status::begin); //wird mit der alten Version nicht aufgerufen
            }   

            friend bool operator!= (const Iterator& a, const Iterator& b)
            {  
                return !(a == b); 
            }

            friend bool operator< (const Iterator& a, const Iterator& b)  
            { 
                return (a.m_ordinalnumber < b.m_ordinalnumber);
            }

            friend bool operator> (const Iterator& a, const Iterator& b)  
            { 
                return (a.m_ordinalnumber > b.m_ordinalnumber);
            }

            friend bool operator<=(const Iterator& a, const Iterator& b)
            { 
                return (a == b || a < b);
            }

            friend bool operator>=(const Iterator& a, const Iterator& b)
            { 
                return (a == b || a > b);
            }

            //Addition mit += (bei allen additionen und subtraktionen Klammerausdrücke testen in catch2)
            /*const*/ Iterator& operator+=(const difference_type& other)
            {   
                if(other >= 0)
                {
                    for(int incCount{}; incCount < other; ++incCount)
                    {
                        ++(*this);
                    }
                }
                else if(other < 0)
                {   
                    long int positivOther {other * -1};
                    for(int decCount{}; decCount < positivOther; ++decCount)
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
            difference_type operator-(const Iterator& other)
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
        explicit UrnOR(int n,int k,int check = 1):m_n { n },
                                                  m_k { k },
                                                  m_z { static_cast<int>(pow(n,k)) }
        {   
            if(m_n < 0 || m_k < 0)                                                    //Kommt neu dazu wegen uint --> int
            {
                throw std::domain_error("UrnOR with negative n or k is not valid.");
            }
            if (check == 1 && m_n == 0 && m_k > 0)
            {
                throw std::domain_error("UrnOR with n == 0 and k > 0 is not valid.");
            }
            
        }

        int n() const
        {
            return m_n;
        }

        int k() const
        {
            return m_k;
        }

        int z() const
        {
            return m_z;
        }

        Iterator begin()
        {
            return Iterator(this,0,Iterator::Status::valid);
        }

        Iterator end()
        {
            return Iterator(this,m_z,Iterator::Status::invalidBack);
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
                for(int posCount {}; posCount < m_k; ++posCount)
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
                for (int downCount { m_k }; downCount > 0; --downCount)
                {
                    if (draw[downCount - 1] < m_n - 1)
                    {   
                        ++draw[downCount - 1];
                        for (int upCount { downCount }; upCount < m_k; ++upCount)
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
                for(int downCount {m_k}; downCount > 0; --downCount)
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

        virtual Draw draw(int ordinalnumber) const
        {   
            Draw draw(m_k, 0);
            if (!(ordinalnumber < m_z) || ordinalnumber < 0)    //uint -> int
            {
                //throw std::overflow_error("There is no valid draw.");
                throw std::out_of_range("There is no valid draw for this ordinalnumber."); //
            }

            for (int posCount {static_cast<int>(m_k - 1)}; posCount >= 0; --posCount)
            {
                for (int timesCount {m_n - 1}; timesCount >= 1; --timesCount)
                {
                    if (static_cast<int>(pow(m_n, posCount)) * timesCount <= ordinalnumber)
                    {
                        draw[posCount] = timesCount;
                        ordinalnumber -= static_cast<int>(pow(m_n, posCount)) * timesCount;
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
        const int m_n,
                  m_k,
                  m_z;
   };

int main()
{   
    UrnOR urn {2,2};
    vector<int> v {1,2,3,4};

    auto it1 {urn.begin()};
    auto it2 {urn.end()};

    auto itv1 {v.begin()};
    auto itv2 {v.end()};

    cout << boolalpha << (it1 == it2) << endl;
    cout << boolalpha << (it1 != it2) << endl;
    cout << boolalpha << (it1 < it2) << endl;
    cout << boolalpha << (it1 > it2) << endl;
    cout << boolalpha << (it1 <= it2) << endl;
    cout << boolalpha << (it1 >= it2) << endl;
    cout << endl;
    cout << boolalpha << (itv1 == itv2) << endl;
    cout << boolalpha << (itv1 != itv2) << endl;
    cout << boolalpha << (itv1 < itv2) << endl;
    cout << boolalpha << (itv1 > itv2) << endl;
    cout << boolalpha << (itv1 <= itv2) << endl;
    cout << boolalpha << (itv1 >= itv2) << endl;

    /*
    auto it {urn.begin()};
    cout << to_string(it[2.6]) << endl;

    auto itv {v.begin()};
    cout << itv[2.3] << endl;


    /*
    int count = urn.end() - urn.begin();
    int vcount = v.end() - v.begin();
    
    int count = urn.rend() - urn.rbegin();
    int vcount = v.rend() - v.rbegin();

    int count = urn.rbegin() - urn.rend();
    int vcount = v.rbegin() - v.rend();
    
    int count = urn.begin() - urn.end();
    int vcount = v.begin() - v.end();
      
    cout << count << endl;
    cout << vcount << endl;


    auto it {urn.begin()};
    it -= 3;
    int count = urn.end() - it;

    auto itv {v.begin()};
    itv -= 3;
    int vcount = v.end() - itv;

    cout << count << endl;
    cout << vcount << endl;

    /*
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
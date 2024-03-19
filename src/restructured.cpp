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
/*
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
*/
/*
template<typename T>
T to_string(T draw)
{
    return draw;
}
*/

//Nötig für die template function, da es keine standart to_string(string draw) gibt
string to_string(string draw)
{
    return draw;
}

//Nötig für die template function, da es keine standart to_string(string draw) gibt
char to_string(char draw)
{
    return draw;
}

template<class T>
string to_string(const vector<T>& draw)
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


uint factorial(const uint& n)
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
            //mit k = 0 Urne möglich aber keine Ziehung (Ergebnis von Rechnung ergibt z = 1)
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
            if(ordinalnumber < 0 || ordinalnumber >= UrnOR::z()) // UrnOR::z(), weil sonst in UrnR UrnR::z() verwendet wird
            {
                throw std::domain_error("There is no valid draw for this ordinalnumber.");
            }
            

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
            return draw(0);
        }

        virtual Draw lastDraw() const
        {
            return draw(z()-1);
        }

        virtual ~UrnOR() = default;
         
    protected:
        const uint m_n,
                   m_k;
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

        virtual uint z() const override
        {   
            //mit k = 0 Urne möglich aber keine Ziehung (Ergebnis von Rechnung ergibt z = 1)
            if(m_k == 0)
            {
                return 0;
            }
            return (factorial(m_n)/factorial(m_n-m_k));
        }

        //Funktioniert aber vielleicht noch Verbesserung?
        /*
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
        */

        virtual Draw draw(uint ordinalnumber) const override
        {   
            if(ordinalnumber < 0 || ordinalnumber >= z())
            {
                throw std::domain_error("There is no valid draw for this ordinalnumber.");
            }

            Draw result;
            Draw elements;
            for(uint fillCount {}; fillCount < m_n; ++fillCount)
            {
                elements.push_back(fillCount);
            }

            uint currentVariations {z()};
            uint index {};
            for(uint upCount{}; upCount < m_k; ++upCount)
            {
                currentVariations /= (m_n-upCount);
                index = ordinalnumber/currentVariations;
                result.push_back(elements.at(index));
                elements.erase(elements.begin()+index);
                ordinalnumber -= index*currentVariations;
            }
            return result;
        }

        virtual Draw nextDraw(Draw draw) const override
        {   
            if(repetitions(draw) || draw == UrnO::draw(z()-1))
            {
                throw std::domain_error("Either the specified draw is incorrect or there is no next valid draw");
            }

            Draw result {draw};
            do
            {
                result = UrnOR::nextDraw(result);
            }while (repetitions(result));
            return result;
        }

        virtual Draw backDraw(Draw draw) const override
        {
            if(repetitions(draw) || draw == UrnO::draw(0))
            {
                throw std::domain_error("Either the specified draw is incorrect or there is no next valid draw");
            }

            Draw result {draw};
            do
            {
                result = UrnOR::backDraw(result);
            }while (repetitions(result));
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

class UrnR: public virtual UrnOR
{
    public:
        explicit UrnR(uint n,uint k,uint check = 3):UrnOR { n,k,check }
        { 
            if (check == 3 && m_n == 0)
            {
                throw std::domain_error("UrnR with n = 0 is not valid.");
            }
        }

        virtual uint z() const override
        {   
            //mit k = 0 Urne möglich aber keine Ziehung (Ergebnis von Rechnung ergibt z = 1)
            if(m_k == 0)
            {
                return 0;
            }
            return ((factorial(m_k+m_n-1))/(factorial(m_k)*factorial(m_n-1)));
        }
        
        virtual Draw draw(uint ordinalnumber) const override
        {   
            if(ordinalnumber < 0 || ordinalnumber >= z())
            {
                throw std::domain_error("There is no valid draw for this ordinalnumber.");
            }
            
            Draw result {};
            int unsortedCount {-1};
            for(uint upCount {}; upCount < UrnOR::z(); ++upCount)
            {   
                result = UrnOR::draw(upCount);
                if(!unsorted(result))
                {   
                    ++unsortedCount;
                    if(unsortedCount == ordinalnumber)
                    {
                        break;
                    }
                }
            }
            return result;

        }

        virtual Draw nextDraw(Draw draw) const override
        {   
            if(unsorted(draw) || draw == UrnR::draw(z()-1))
            {
                throw std::domain_error("Either the specified draw is incorrect or there is no next valid draw");
            }

            Draw result {draw};
            do
            {
                result = UrnOR::nextDraw(result);
            }while (unsorted(result));
            return result;
        }

        virtual Draw backDraw(Draw draw) const override
        {
            if(unsorted(draw) || draw == UrnR::draw(0))
            {
                throw std::domain_error("Either the specified draw is incorrect or there is no next valid draw");
            }

            Draw result {draw};
            do
            {
                result = UrnOR::backDraw(result);
            }while (unsorted(result));
            return result;
        }

        bool unsorted(const Draw& unsortDraw) const
        {
            for (uint posCount {}; posCount < m_k - 1; ++posCount)
            {
                if (unsortDraw[posCount] > unsortDraw[posCount + 1])
                {
                    return true;
                }
            }
            return false;
        }
};

class Urn: public UrnO, public UrnR
{
    public:
        explicit Urn(uint n,uint k,uint check = 3):UrnOR { n,k },
                                                   UrnO { n,k,1 },
                                                   UrnR { n,k,1 }{}

        virtual uint z() const override
        {   
            //mit k = 0 Urne möglich aber keine Ziehung (Ergebnis von Rechnung ergibt z = 1)
            if(m_k == 0)
            {
                return 0;
            }
            return ((factorial(m_n))/(factorial(m_n-m_k)*factorial(m_k)));
        }

        virtual Draw draw(uint ordinalnumber) const override
        {
            if(ordinalnumber < 0 || ordinalnumber >= z())
            {
                throw std::domain_error("There is no valid draw for this ordinalnumber.");
            }
            
            Draw result {};
            int drawCount {-1};
            for(uint upCount {}; upCount < UrnOR::z(); ++upCount)
            {   
                result = UrnOR::draw(upCount);
                if(!unsorted(result) && !repetitions(result))
                {   
                    ++drawCount;
                    if(drawCount == ordinalnumber)
                    {
                        break;
                    }
                }
            }
            return result;
        }

        virtual Draw nextDraw(Draw draw) const override
        {   
            if(repetitions(draw) || unsorted(draw) || draw == Urn::draw(z()-1))
            {
                throw std::domain_error("Either the specified draw is incorrect or there is no next valid draw");
            }

            Draw result {draw};
            do
            {
                result = UrnOR::nextDraw(result);
            }while (repetitions(result) || unsorted(result));
            return result;
        }

        virtual Draw backDraw(Draw draw) const override
        {
            if(repetitions(draw) || unsorted(draw) || draw == Urn::draw(0))
            {
                throw std::domain_error("Either the specified draw is incorrect or there is no next valid draw");
            }

            Draw result {draw};
            do
            {
                result = UrnOR::backDraw(result);
            }while (repetitions(result) || unsorted(result));
            return result;
        }
};

//Generic Urn

template<bool O, bool R>
struct UrnSelector
{
    using UrnType = UrnOR;
};

template<>
struct UrnSelector<true, false>
{
    using UrnType = UrnO;
};

template <>
struct UrnSelector<false, true>
{
    using UrnType = UrnR;
};

template <>
struct UrnSelector<false, false> 
{
    using UrnType = Urn;
};

template<class T, bool ORDER = true, bool REPETITION = true>
class GenericUrn    //Keine Vererbung von UrnOR, da sonst draw, firstDraw, lastDraw, ... override anschlägt
{   
    public:
    class Iterator
    {   
        public:
            using iterator_category = std::random_access_iterator_tag;  //std::bidirectional_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = vector<T>; //vector<unsigned int>
            using pointer           = vector<T>*;  
            using reference         = const vector<T>; //Kommentar anmerken
            using size_type         = std::size_t;  //https://en.cppreference.com/w/cpp/types/size_t

            //Iterators: constructible, copy-constructible, copy-assignable, destructible and swappable
            enum class Status
            {
                invalidFront,
                valid,
                invalidBack
            };
            
            Iterator(const GenericUrn<T,ORDER,REPETITION>* urn, const uint& ordinalnumber, const Status& status): m_itUrn{ urn },
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
                return (*m_itUrn).n();
            }

            uint k() const
            {
                return (*m_itUrn).k();
            }

            uint z() const
            {
                return (*m_itUrn).z();
            }

            int ordinalnumber() const
            {
                return m_ordinalnumber;
            }
            
            const value_type operator*() const 
            {   
                if(m_ordinalnumber >= z() || m_ordinalnumber < 0)
                {   
                    throw std::domain_error("There is no valid draw for this ordinalnumber.");
                    //Gibt beim std::vector --it Loop von end zu begin einen Segmantion fault
                    //bei string also ist es so okay (vielleicht noch eine Überladung für int, float, ...
                }
                return (*m_itUrn).draw(m_ordinalnumber);
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
                    throw std::domain_error("There is no valid draw for this ordinalnumber.");
                    //Gleiches Problem wie bei operator *()
                }
                return (*m_itUrn).draw(index);
            }
            
            ~Iterator() = default;

        protected:
            const GenericUrn<T,ORDER,REPETITION>* m_itUrn;
            int m_ordinalnumber;
            Status m_status;
    };

    public:
        GenericUrn(uint k, const std::vector<T>& elements):m_urn {static_cast<uint>(elements.size()),k}, 
                                                           m_elements {elements}{}
        uint n() const 
        {
            return m_urn.n();
        }

        uint k() const 
        {
            return m_urn.k();
        }

        uint z() const
        {
            return m_urn.z();
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
        
        vector<T> to_element(const Draw& draw) const
        {
            vector<T> result{};
            for(auto i: draw)
            {
                result.push_back(m_elements.at(i));
            }
            return result;
        }

        auto draw(uint ordinalnumber) const
        {
            return to_element(m_urn.draw(ordinalnumber));
        }
        
        /*
        //Konvertiert den uint Draw direkt zu den m_elements
        vector<T> draw(uint ordinalnumber)
        {
            vector<T> result {};
            Draw draw {m_urn.draw(ordinalnumber)};
            for(auto i: draw)
            {
                result.push_back(m_elements.at(i));
            }
            return result;
        }
        */

        auto nextDraw(const vector<T>& draw) const
        {   
            Draw nextDraw {};
            for(uint posCount {}; posCount < draw.size(); ++posCount)
            {
                for(uint upCount {}; upCount < m_elements.size(); ++upCount)
                {
                    if(draw.at(posCount) == m_elements.at(upCount))
                    {
                        nextDraw.push_back(upCount);
                    }
                }
            }
            return to_element(m_urn.nextDraw(nextDraw));
        }

        auto backDraw(const vector<T>& draw) const
        {
            Draw backDraw {};
            for(uint posCount {}; posCount < draw.size(); ++posCount)
            {
                for(uint upCount {}; upCount < m_elements.size(); ++upCount)
                {
                    if(draw.at(posCount) == m_elements.at(upCount))
                    {
                        backDraw.push_back(upCount);
                    }
                }
            }
            return to_element(m_urn.backDraw(backDraw));
        }

        auto firstDraw()
        {
            return to_element(m_urn.firstDraw());
        }

        auto lastDraw()
        {
            return to_element(m_urn.lastDraw());
        }

    private:
        using UrnType = typename UrnSelector<ORDER,REPETITION>::UrnType;
        UrnType m_urn;
        std::vector<T> m_elements;
};
/*
class Person
        {
            public:
                Person(string name, uint age): m_name {name}, m_age{age}{}

                string getName()
                {
                    return m_name;
                }

                uint getAge()
                {
                    return m_age;
                }

                bool operator==(const Person& other) const
                {
                    return (m_name == other.m_name && m_age == other.m_age);
                }

            private:
                string m_name {};
                uint m_age {};  
        };

        string outputPerson(vector<Person> draw)
        {   
            string stdraw {};
            for(uint posCount{}; posCount < draw.size(); ++posCount)
            {
                stdraw += (draw.at(posCount).getName()) + "," + to_string((draw.at(posCount).getAge()));
                if(posCount != (draw.size()-1))
                {
                    stdraw += " ";
                }
            }
            return stdraw;
        }

int main()
{   
    
    GenericUrn<string,true,true> u {2,{"A","B"}};

    GenericUrn<Person,true,true> ur {2,{{"Theo",12},{"Jonas",13}}};

    auto it {ur.begin()};

    cout << outputPerson(it[29]) << endl;

    return 0;
}
*/
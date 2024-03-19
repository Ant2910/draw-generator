/*! 
 * \file urn.cpp
 * \author Anton Hempel, Ulrich Eisenecker
 * \date March 18, 2024
 *  
 * Implementation file of the draw generator
 * 
 * Implementation of the urn models.
 * UrnOR – urn where the order is important and which contains repetitions.
 * UrnO – urn where the order is important and does not include repetitions.
 * UrnR – urn with unimportant order and with repetitions.
 * Urn – urn with unimportant order and without repetitions.
 */

#include <vector>
#include <string> 
//#include <exception>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iterator>

#include "newurn.hpp"

namespace urn
{
    using uint = unsigned int;       
    using Draw = std::vector<uint>;

    //Helper functions
    
    uint factorial(const uint& n)
    {
        if(n == 0)
        {
            return 1;
        }
        return n*factorial(n-1);
    }

    //Iterator

    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Draw;
    using pointer           = Draw*;  
    using reference         = const Draw;
    using size_type         = std::size_t;

    enum class UrnOR::Iterator::Status
    {
        invalidFront,
        valid,
        invalidBack
    };

    UrnOR::Iterator::Iterator(const UrnOR* urn, const uint& ordinalnumber, const Status& status): m_urn{ urn },
                                                                                 m_ordinalnumber{ static_cast<int>(ordinalnumber) },
                                                                                 m_status { status }{}

    UrnOR::Iterator::Iterator() = default;

    std::string UrnOR::Iterator::status() const
    {
        switch(m_status)
        {
            case Status::invalidFront: return "invalidFront"; break;
            case Status::valid: return "valid"; break;
            case Status::invalidBack: return "invalidBack"; break;
            default: throw std::invalid_argument("m_status is invalid."); break;
        }
    }

    uint UrnOR::Iterator::n() const
    {
        return (*m_urn).n();
    }

    uint UrnOR::Iterator::k() const
    {
        return (*m_urn).k();
    }

    uint UrnOR::Iterator::z() const
    {
        return (*m_urn).z();
    }

    int UrnOR::Iterator::ordinalnumber() const
    {
        return m_ordinalnumber;
    }

    const value_type UrnOR::Iterator::operator*() const 
    {   
        if(m_ordinalnumber >= z() || m_ordinalnumber < 0)
        {
            return Draw((k()), 0);
        }
        return (*m_urn).draw(m_ordinalnumber);
    }

    UrnOR::Iterator& UrnOR::Iterator::operator++()
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
                    
    UrnOR::Iterator UrnOR::Iterator::operator++(int)
    { 
        auto temp {*this};
        ++(*this);
        return temp;
    }

    UrnOR::Iterator& UrnOR::Iterator::operator--()
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
                
    UrnOR::Iterator UrnOR::Iterator::operator--(int)
    {
        auto temp {*this};
        --(*this);
        return temp;
    }

    bool UrnOR::Iterator::operator== (const Iterator& other) const
    { 
        return (m_ordinalnumber == other.m_ordinalnumber);
    }   

    bool UrnOR::Iterator::operator!= (const Iterator& other) const
    {  
        return !(*this == other); 
    }

    bool UrnOR::Iterator::operator< (const Iterator& other) const
    { 
        return (m_ordinalnumber < other.m_ordinalnumber);
    }

    bool UrnOR::Iterator::operator> (const Iterator& other) const 
    { 
                    return (m_ordinalnumber > other.m_ordinalnumber);
    }

    bool UrnOR::Iterator::operator<=(const Iterator& other) const
    { 
        return (*this == other || *this < other);
    }

    bool UrnOR::Iterator::operator>=(const Iterator& other) const
    { 
        return (*this == other || *this > other);
    }

    UrnOR::Iterator& UrnOR::Iterator::operator+=(const difference_type& other)
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

    UrnOR::Iterator UrnOR::Iterator::operator+(const difference_type& n) const
    { 
        auto temp {*this};
        return (temp += n);
    }
                
    UrnOR::Iterator operator+(const difference_type& n, const UrnOR::Iterator& other) 
    {
        return other + n;
    }
                
    UrnOR::Iterator& UrnOR::Iterator::operator-=(const difference_type& n)
    {
        long int negativ {n * -1};
        (*this) += negativ;
        return *this;
    }

    UrnOR::Iterator UrnOR::Iterator::operator-(const difference_type& n) const
    { 
        auto temp {*this};
        return (temp -= n);
    }

    difference_type UrnOR::Iterator::operator-(const Iterator& other) const
    { 
        return m_ordinalnumber - other.m_ordinalnumber;
    }

    reference UrnOR::Iterator::operator[](size_type index) const 
    { 
        if(index >= z() || index < 0)
        {
            return Draw((k()), 0);
        }
        return (*m_urn).draw(index);
    }

    UrnOR::Iterator::~Iterator() = default;

    //UrnOR – urn where the order is important and which contains repetitions.

    UrnOR::UrnOR(uint n,uint k,uint check):m_n { n },
                                               m_k { k }
    {   
        if (check == 1 && m_n == 0 && m_k > 0)
        {
            throw std::domain_error("UrnOR with n == 0 and k > 0 is not valid.");
        }
            
    }

    uint UrnOR::n() const
    {
        return m_n;
    }

    uint UrnOR::k() const
    {
        return m_k;
    }

    uint UrnOR::z() const 
    {   
        if(m_k == 0)    
        {
            return 0;
        }
        return static_cast<uint>(std::pow(m_n,m_k));
    }

    UrnOR::Iterator UrnOR::begin()
    {
        return Iterator(this,0,Iterator::Status::valid);
    }

    UrnOR::Iterator UrnOR::end()
    {
        return Iterator(this,z(),Iterator::Status::invalidBack);
    }

    auto UrnOR::rbegin()
    {   
        return std::make_reverse_iterator(end());
    }

    auto UrnOR::rend()
    {
        return std::make_reverse_iterator(begin());
    }

    [[nodiscard]] bool UrnOR::valid(const Draw& draw) const
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

    Draw UrnOR::nextDraw(Draw draw) const
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

    Draw UrnOR::backDraw(Draw draw) const
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

    Draw UrnOR::draw(uint ordinalnumber) const
    {   
        if(ordinalnumber < 0 || ordinalnumber >= UrnOR::z())
        {
            throw std::domain_error("There is no valid draw for this ordinalnumber.");
        }
            
        Draw draw(m_k, 0);
        for (int posCount {static_cast<int>(m_k - 1)}; posCount >= 0; --posCount)
        {
            for (uint timesCount {m_n - 1}; timesCount >= 1; --timesCount)
            {
                if (static_cast<uint>(std::pow(m_n, posCount)) * timesCount <= ordinalnumber)
                {
                    draw[posCount] = timesCount;
                    ordinalnumber -= static_cast<uint>(std::pow(m_n, posCount)) * timesCount;
                    break;
                }
            }
        }
        std::reverse(draw.begin(), draw.end());
        return draw;
    }

    Draw UrnOR::firstDraw() const
    {
        return draw(0);
    }

    Draw UrnOR::lastDraw() const
    {
        return draw(z()-1);
    }

    UrnOR::~UrnOR() = default;

    //UrnO – urn where the order is important and does not include repetitions.

    UrnO::UrnO(uint n,uint k,uint check): UrnOR { n,k,check }
    {   
        if (check == 2 && m_k > m_n)
        {
            throw std::domain_error("UrnO with k > n is not valid.");
        }
    }

    uint UrnO::z() const
    {   
        if(m_k == 0)
        {
            return 0;
        }
        return (factorial(m_n)/factorial(m_n-m_k));
    }

    Draw UrnO::draw(uint ordinalnumber) const
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

    Draw UrnO::nextDraw(Draw draw) const
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

    Draw UrnO::backDraw(Draw draw) const
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

    bool UrnO::repetitions(const Draw& repDraw) const
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

    //UrnR – urn with unimportant order and with repetitions.   

    UrnR::UrnR(uint n,uint k,uint check):UrnOR { n,k,check }
    { 
        if (check == 3 && m_n == 0)
        {
            throw std::domain_error("UrnR with n = 0 is not valid.");
        }
    }

    uint UrnR::z() const
    {   
            
        if(m_k == 0)
        {
            return 0;
        }
        return ((factorial(m_k+m_n-1))/(factorial(m_k)*factorial(m_n-1)));
    }
        
    Draw UrnR::draw(uint ordinalnumber) const
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

    Draw UrnR::nextDraw(Draw draw) const
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

    Draw UrnR::backDraw(Draw draw) const
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

    bool UrnR::unsorted(const Draw& unsortDraw) const
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

    //Urn – urn with unimportant order and without repetitions.

    Urn::Urn(uint n,uint k,uint check):UrnOR { n,k },
                                       UrnO { n,k,1 },
                                       UrnR { n,k,1 }{}

    uint Urn::z() const
    {   
        if(m_k == 0)
        {
            return 0;
        }
        return ((factorial(m_n))/(factorial(m_n-m_k)*factorial(m_k)));
    }

    Draw Urn::draw(uint ordinalnumber) const
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

    Draw Urn::nextDraw(Draw draw) const
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

    Draw Urn::backDraw(Draw draw) const
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
}
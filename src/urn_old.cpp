/*! 
 * \file urn_old.cpp
 * \author Ulrich Eisenecker
 * \date March 10, 2023
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
#include <iostream>     // Because of cerr
#include <cstdlib>      // Because of exit()
using namespace std;

#include "urn_old.hpp"


namespace urn_old
{
   using uint = unsigned int;       
   using Draw = std::vector<uint>;  

   
   //UrnOR – urn where the order is important and which contains repetitions.

    UrnOR::UrnOR(uint n,uint k,uint check):m_n { n },
                                           m_k { k },
                                           m_balls(k,0)
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

    uint UrnOR::at(uint index) const
    {
        return m_balls.at(index);
    }

    uint UrnOR::operator[](uint index) const
    {
        return m_balls[index];
    }

    [[nodiscard]] bool UrnOR::next()
    {
        for (uint down { m_k }; down > 0; --down)
        {
            if (m_balls[down - 1] < m_n - 1)
            {   
                ++m_balls[down - 1];
                for (uint up { down }; up < m_k; ++up)
                {
                    m_balls[up] = 0;
                }
                return true;
            }
        }
        return false;
    }
    
    UrnOR::~UrnOR() = default;

    //UrnO – urn where the order is important and does not include repetitions.

    UrnO::UrnO(uint n,uint k,uint check):UrnOR { n,k,check }
    { 
        if (check == 2 && m_k > m_n)
        {
            throw std::domain_error("UrnO with k > n is not valid.");
        }
        for (uint i { 1 }; i < m_k; ++i)
        {
            m_balls[i] = i;
        }
    }

    [[nodiscard]] bool UrnO::next()
    {
        while (UrnOR::next())
        {
            if (!repetitions())
            {
                return true;
            };
        }
        return false;
    }
    
    bool UrnO::repetitions() const
    {
        for (uint i { 0 };i < m_k - 1; ++i)
        {
            for (uint j { i + 1 }; j < m_k; ++j)
            {
                if (m_balls[i] == m_balls[j])
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

    [[nodiscard]] bool UrnR::next()
    {
        while (UrnOR::next())
        {
            if (!unsorted())
            {
                return true;
            };
        }
        return false;
    }
    
    bool UrnR::unsorted() const
    {
        for (uint i { 0 };i < m_k - 1; ++i)
        {
            if (m_balls[i] > m_balls[i + 1])
            {
                return true;
            }
        }
        return false;
    }
  
   //Urn – urn with unimportant order and without repetitions.
   
    Urn::Urn(uint n,uint k):UrnOR { n,k },
                            UrnO { n,k,1 },
                            UrnR { n,k,1 }
    { 
        for (uint i { 1 }; i < m_k; ++i)
        {
            m_balls[i] = i;
        }
    }
         
    [[nodiscard]] bool Urn::next()
    {
        while (UrnOR::next())
        {
            if (!unsorted() && !repetitions())
            {
                return true;
            };
        }
        return false;
    } 
}
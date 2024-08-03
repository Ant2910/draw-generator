/*! 
 * \file urn_old.hpp
 * \author Ulrich Eisenecker
 * \date June 14, 2023
 *  
 * Header file of the draw generator
 * 
 * Implementation of the urn models.
 * UrnOR – urn where the order is important and which contains repetitions.
 * UrnO – urn where the order is important and does not include repetitions.
 * UrnR – urn with unimportant order and with repetitions.
 * Urn – urn with unimportant order and without repetitions.
 * 
 * Source:
 * English: https://www.mathsisfun.com/combinatorics/combinations-permutations.html
 * 
 * German: https://www.massmatics.de/merkzettel/#!879:Urnenmodelle 
 */

/*!
 * Include guard for urn_old.hpp
 */

#ifndef URN_OLD_HPP
#define URN_OLD_HPP

#include <vector>
#include <iostream> // Because of cerr
#include <exception> 

/*! 
 * \namespace urn
 * \brief Namespace for the urn models.
 * Namespace to avoid name collisions.
 */

namespace urn_old
{
   using uint = unsigned int;       /*!< Using decleration to represent the set of natural numbers. */
   using Draw = std::vector<uint>;  /*!< Using decleration to represent a combination and permutation. */

   /*!
    * \class UrnOR – urn where the order is important and which contains repetitions.
    */

   class UrnOR
   {
      public:
         /*!
          * \brief Constructor for UrnOR.
          * Constructs an exampler of UrnOR.
          * Declared as explicit to prevent implicit calls.
          * Initializes m_balls which creates a vector<> with k elements, each with the value 0.
          * The check parameter is not intended to be specified by the user.
          * The constructor body performs a check that is specific for the UrnOR, if the check value is 1.
          * If the UrnOR exemplar to be created is invalid, an exception is thrown.
          * @param[in] n      The number of balls inside the urn.
          * @param[in] k      The size of a draw from the urn.
          * @param[in] check  The check value.
          */
         explicit UrnOR(uint n,uint k,uint check = 1);

         /*!
          * \brief Getter method which returns m_n.
          * \return m_n the number of balls inside the urn.
          */
         uint n() const;
         
         /*!
          * \brief Getter method which returns m_k.
          * \return m_k the size of a draw from the urn.
          */
         uint k() const;

         /*!
          * \brief Getter method for accessing individual balls/elements.
          * Returns the element specified by index as value.
          * Method uses the std::vector<>::at() function.
          * Performs index checking.
          * @param[in] index Index of the element to be accessed. 
          */
         uint at(uint index) const;
         
         /*!
          * \brief Overload of the [] index operator
          * Returns the element specified by index as value.
          * @param[in] index Index of the element to be accessed.
          */
         uint operator[](uint index) const;

         /*!
          * \brief Method to generate the next draw (order important, with repetition).
          * Its return value must not be ignored.
          * If there is a valid next draw, the member function returns true, otherwise false.
          * 
          * \return true/false depends if there is a next draw.
          */
         [[nodiscard]] virtual bool next();
         
         /*!
          * \brief Virtual destructor for UrnOR.
          * Virtual destructor to be a valid base class.
          * Destructor is defaulted.
          */
         virtual ~UrnOR();

      protected:
         const uint m_n,   //!< The number of balls inside the urn.
                    m_k;   //!< The size of a draw from the urn.
         Draw m_balls;     //!< Changing combinations and permutations of the balls.
   };

   /*!
    * \class UrnO – urn where the order is important and does not include repetitions.
    */

   class UrnO: public virtual UrnOR
   {
      public:
         /*!
          * \brief Constructor for UrnO.
          * Constructs an exampler of UrnO.
          * Declared as explicit to prevent implicit calls.
          * Constructor calls the constructor of UrnOR to create an exampler.
          * The check parameter is not intended to be specified by the user.
          * The constructor body performs a check that is specific for the UrnO, if the check value is 2.
          * The constructor body executes a for loop to initialize m_balls correctly (no repetitions).
          * If the UrnO exemplar to be created is invalid, an exception is thrown.
          * 
          * @param[in] n      The number of balls inside the urn.
          * @param[in] k      The size of a draw from the urn.
          * @param[in] check  The check value.
          */
         explicit UrnO(uint n,uint k,uint check = 2);
         
         /*!
          * \brief Method to generate the next draw (order important, without repetition).
          * Calls UrnOR::next() and additionally checks if the previously generated draw contains a duplicate element.
          * Its return value must not be ignored.
          * If there is a valid next draw, the member function returns true, otherwise false.
          * 
          * \return true/false depends if there is a next draw.
          */
         [[nodiscard]] bool next() override;
         
      protected:
         /*!
          * \brief Method to search for duplicate elements in m_balls. 
          */
         bool repetitions() const;
   };

   /*!
    * \class UrnR – urn with unimportant order and with repetitions.
    */
   class UrnR: virtual public UrnOR
   {
      public:
         /*!
          * \brief Constructor for UrnR.
          * Constructs an exampler of UrnR.
          * Declared as explicit to prevent implicit calls.
          * Constructor calls the constructor of UrnOR to create an exampler.
          * The check parameter is not intended to be specified by the user.
          * The constructor body performs a check that is specific for the UrnR, if the check value is 3.
          * If the UrnR exemplar to be created is invalid, an exception is thrown.
          * 
          * @param[in] n      The number of balls inside the urn.
          * @param[in] k      The size of a draw from the urn.
          * @param[in] check  The check value.
          */
         explicit UrnR(uint n,uint k,uint check = 3);
         
         /*!
          * \brief Method to generate the next draw (order not important, with repetition).
          * Calls UrnOR::next() and additionally checks if an element with a lower index value is greater than its neighbor element with index value plus one.
          * Its return value must not be ignored.
          * If there is a valid next draw, the member function returns true, otherwise false.
          * 
          * \return true/false depends if there is a next draw.
          */
         [[nodiscard]] bool next() override;
         
      protected:
         /*!
          * \brief Method to check if an element with a lower index value is greater than its neighbor element with index value plus one.
          */
         bool unsorted() const;
   };
   
   /*!
    * \class Urn – urn with unimportant order and without repetitions.
    */
   class Urn: public UrnO, public UrnR
   {
      public:
         /*!
          * \brief Constructor for Urn.
          * Constructs an exampler of Urn.
          * Declared as explicit to prevent implicit calls.
          * Constructor calls the constructors of 
          * UrnOR { n,k }, UrnO { n,k,1 } and UrnR { n,k,1 }
          * The constructor body does not perform any check. The checks are performed by the UrnOR constructor.
          * 
          * @param[in] n      The number of balls inside the urn.
          * @param[in] k      The size of a draw from the urn.
          */ 
         explicit Urn(uint n,uint k);

         /*!
          * \brief Method to generate the next draw (order not important, without repetition).
          * Calls UrnOR::next() and additionally checks that the current draw is not unsorted and that it does not contain repetitions.
          * Its return value must not be ignored.
          * If there is a valid next draw, the member function returns true, otherwise false.
          * 
          * \return true/false depends if there is a next draw.
          */                            
         [[nodiscard]] bool next() override;
   };

   /*!
    * \struct UrnSelector is used to set the UrnType in the template class GenericUrn.
    * The standard UrnType is UrnOR.
    * 
    * Note for the compilation of the program. 
    * Since C++14 an explicit specialization within a class/class template is possible. 
    * Unfortunately it seems that the G++ compiler (GNU c++ compiler) does not support this feature yet.
    * 
    * @tparam O     Is order important?
    * @tparam R     Is repetition important?        
    */
   template <bool O, bool R>
   struct UrnSelector; 

   /*!
    * \struct UrnSelector specialization for order important and repetition not important.
    * The UrnType is UrnO.      
    */
   template <>
   struct UrnSelector<true, false>;

   /*!
    * \struct UrnSelector specialization for order not important and repetition important.
    * The UrnType is UrnR.      
    */
   template <>
   struct UrnSelector<false, true>;

   /*!
    * \struct UrnSelector specialization for order not important and repetition not important.
    * The UrnType is Urn.      
    */
   template <>
   struct UrnSelector<false, false>; 

   /*!
    * \class GenericUrn - Template-Wrapper for the urn models/draw-generator.
    * 
    * @tparam T            Type for which the GenericUrn is to be created.
    * @tparam ORDER        Is order important?
    * @tparam REPETITION   Is repetition important?      
    */
   template <typename T,bool ORDER = true,bool REPETITION = true>
   class GenericUrn
   {
      public:
         /*!
          * \brief Constructor for GenericUrn
          * Constructs an exampler of GenericUrn.
          * Calls the constructor for m_urn with 
          * n = elements.size(), k. 
          * The UrnType of m_urn is set by UrnSelector.
          * Initializes m_elements with elements.
          * 
          * @param[in] k         The size of a draw from the urn.
          * @param[in] elements  Diffrent elements inside of the urn.
          */
         GenericUrn(uint k,const std::vector<T>& elements);

         /*!
          * \brief Getter method which returns m_n.
          * Calls the n() function of the UrnType of m_urn.
          * \return m_n the number of balls inside the urn.
          */   
         uint n() const;
         
         /*!
          * \brief Getter method which returns m_k.
          * Calls the k() function of the UrnType of m_urn.
          * \return m_k the size of a draw from the urn.
          */
         uint k() const;
         
         /*!
          * \brief Getter method for accessing individual balls/elements.
          * Returns the element specified by index as value.
          * Method uses the std::vector<>::at() function.
          * Calls the at() function of the UrnType of m_urn.
          * @param[in] index Index of the element to be accessed. 
          */
         const T& at(uint index) const;
         
         /*!
          * \brief Overload of the [] index operator
          * Returns the element specified by index as value.
          * Uses the []operator of the UrnType of m_urn.
          * @param[in] index Index of the element to be accessed.
          */
         const T& operator[](uint index) const;
         
         /*!
          * \brief Method to generate the next draw.
          * Calls the next() function of the UrnType of m_urn.
          * Its return value must not be ignored.
          * If there is a valid next draw, the member function returns true, otherwise false.
          * 
          * \return true/false depends if there is a next draw.
          */
         [[nodiscard]] virtual bool next();
                 
      private:
         using UrnType = typename UrnSelector<ORDER,REPETITION>::UrnType; /*!< Using decleration as alias for the urn types. */
         UrnType m_urn;                /*!< Exampler of an urn of type UrnType. */
         std::vector<T> m_elements;    /*!< Vector of type T containing the different elements inside the urn. */
   };

   //Attention: The designations given may differ depending on the source.
   template <class T> // According to https://en.wikipedia.org/wiki/Permutation
   using Permutation = GenericUrn<T,true,true>;          /*!< Using decleration as alias for a GenericUrn of UrnType UrnOR. */

   template <class T> // According to https://en.wikipedia.org/wiki/Partial_permutation
   using PartialPermutation = GenericUrn<T,true,false>;  /*!< Using decleration as alias for a GenericUrn of UrnType UrnO. */

   template <class T> // According to https://en.wikipedia.org/wiki/Combination
   using MultiCombination = GenericUrn<T,false,true>;    /*!< Using decleration as alias for a GenericUrn of UrnType UrnR. */

   template <class T> // According to https://en.wikipedia.org/wiki/Combination
   using Combination = GenericUrn<T,false,false>;        /*!< Using decleration as alias for a GenericUrn of UrnType Urn. */

   /*!
    * Include guard for definitions.tpp
    * definitions.tpp contains the definitions of the class/function templates
    */
   #if __has_include("definitions_old.tpp")
   #include "definitions_old.tpp"
   #endif //__has_include
}
#endif // URN_OLD_HPP
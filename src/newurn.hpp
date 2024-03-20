/*! 
 * \file urn.hpp
 * \author Anton Hempel, Ulrich Eisenecker
 * \date March 18, 2024
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
 * Include guard for urn.hpp
 */

#ifndef URN_HPP
#define URN_HPP

#include <vector>
#include <string> 
//#include <exception>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iterator>

/*! 
 * \namespace urn
 * \brief Namespace for the urn models.
 * Namespace to avoid name collisions.
 */

namespace urn
{
    using uint = unsigned int;       /*!< Using decleration to represent the set of natural numbers. */
    using Draw = std::vector<uint>;  /*!< Using decleration to represent a combination and permutation. */

    //Helper function
    
    /*!
     * \brief Helper function for calculating the faculty.
     * \return Faculty of n of type uint.
     */
    uint factorial(const uint& n);

    /*!
     * \class UrnOR – urn where the order is important and which contains repetitions.
     */

    class UrnOR
    {   
        public:

            /*!
             * \class Iterator 
             * \brief Iterator which fulfills the requirements as a random access iterator.
             * The behavior is based on the std::vector class. 
             * The special feature of the iterator is that it does not use a memory structure like a vector.
             */

            class Iterator
            {   
                public:
                    using iterator_category = std::random_access_iterator_tag;  /*!< Using decleration for the iterator category which is std::random_access_iterator.*/
                    using difference_type   = std::ptrdiff_t;                   /*!< Using decleration for the difference type which is ptrdiff_t.*/
                    using value_type        = Draw;                             /*!< Using decleration for the value type which is Draw (vector<uint>).*/
                    using pointer           = Draw*;                            /*!< Using decleration for the pointer which is Draw* (vector<uint>*).*/
                    using reference         = const Draw;                       /*!< Using decleration for the reference. The type is const Draw due to an error in the standard library when using the std::make_reverse_iterator (http://gcc.gnu.org/PR51823).*/
                    using size_type         = std::size_t;                      /*!< Using decleration for the size type which is size_t.*/

                    /*!
                     * \enum enum class Status
                     * \brief Represents the current status of the iterator.
                     */
                    enum class Status;

                    /*!
                     * \brief Constructor for Iterator.
                     * Constructs an exampler of Iterator.
                     * @param[in] urn               Pointer to an urn on which the various functions are executed.
                     * @param[in] ordinalnumber     Indicates the ordinal number of a draw.
                     * @param[in] check             Indicates the status of the iterator.
                     */
                    Iterator(const UrnOR* urn, const uint& ordinalnumber, const Status& status);

                    /*!
                     * \brief Standard constructor for Iterator.
                     * Is a requirement for the ranges::random_access_iterator concept.
                     */
                    Iterator();

                    /*!
                     * \brief Getter method which returns the Status of the iterator.
                     * \return Status of iterator as std::string.
                     */
                    std::string status() const;
                    
                    /*!
                     * \brief Getter method which returns n.
                     * \return n the number of balls inside the urn.
                     */
                    uint n() const;

                    /*!
                     * \brief Getter method which returns k.
                     * \return k the size of a draw from the urn.
                     */
                    uint k() const;

                    /*!
                     * \brief Getter method which returns z.
                     * \return z the number of all possible draws.
                     */
                    uint z() const;
    
                    /*!
                     * \brief Getter method which returns ordinalnumber.
                     * \return ordinalnumber the ordinal number of the current draw.
                     */
                    int ordinalnumber() const;
            
                    /*!
                     * \brief Operator for pointer dereferencing. 
                     * \return Returns the current draw of the iterator as value type.
                     * If the iterator is outside the range, a vector filled with zeros is returned. 
                     */
                    const value_type operator*() const; 
                    
                    /*!
                     * \brief Operator for pre-incrementation. 
                     * \return Returns the incremented iterator. 
                     */
                    Iterator& operator++();
        
                    /*!
                     * \brief Operator for post-incrementation. 
                     * \return Returns the iterator before incrementation. 
                     */
                    Iterator operator++(int);
            
                    /*!
                     * \brief Operator for pre-decrementation. 
                     * \return Returns the decremented iterator. 
                     */
                    Iterator& operator--();
      
                    /*!
                     * \brief Operator for post-decrementation. 
                     * \return Returns the iterator before decrementation. 
                     */
                    Iterator operator--(int);

                    /*!
                     * \brief Operator for equal to comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator== (const Iterator& other) const;

                    /*!
                     * \brief Operator for not equal to comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator!= (const Iterator& other) const;

                    /*!
                     * \brief Operator for less than comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator< (const Iterator& other) const;

                    /*!
                     * \brief Operator for greater than comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator> (const Iterator& other) const; 

                    /*!
                     * \brief Operator for less than or equal to comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator<=(const Iterator& other) const;

                    /*!
                     * \brief Operator for greater than or equal to comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator>=(const Iterator& other) const;


                    /*!
                     * \brief Operator for addition assignment. 
                     * \return Returns the incremented iterator. 
                     */
                    Iterator& operator+=(const difference_type& other);

                    /*!
                     * \brief Operator for addition. 
                     * \return Returns the sum of iterator and difference type n. 
                     */
                    Iterator operator+(const difference_type& n) const;

                    /*!
                     * \brief Operator for addition (outside class definition). 
                     * \return Returns the sum of iterator and difference type n. 
                     */
                    friend Iterator operator+(const difference_type& n, const Iterator& other); 

                    /*!
                     * \brief Operator for substraction assignment. 
                     * \return Returns the decremented iterator. 
                     */
                    Iterator& operator-=(const difference_type& n);

                    /*!
                     * \brief Operator for substraction. 
                     * \return Returns the difference of iterator and difference type n. 
                     */
                    Iterator operator-(const difference_type& n) const;

                    /*!
                     * \brief Operator for distance. 
                     * \return Returns the distance between the two iterators.
                     */
                    difference_type operator-(const Iterator& other) const;

                    /*!
                     * \brief Operator for index. 
                     * \return Returns the draw to the given index.
                     */
                    reference operator[](size_type index) const; 

                    /*!
                     * \brief Destructor for Iterator.
                     * Destructor is defaulted.
                     */
                    ~Iterator();

                protected:
                    const UrnOR* m_urn;     //!< Pointer to an urn on which the various functions are executed.
                    int m_ordinalnumber;    //!< Indicates the ordinal number of a draw.
                    Status m_status;        //!< Indicates the status of the iterator
        };

        public:
            /*!
             * \brief Constructor for UrnOR.
             * Constructs an exampler of UrnOR.
             * Declared as explicit to prevent implicit calls.
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
             * \brief Getter method which returns z.
             * \return z the number of all possible draws.
             */
            virtual uint z() const; 

            /*!
             * \brief Begin iterator.
             * \return Returns an iterator pointing to the first element in the sequence.
             */
            Iterator begin();

            /*!
             * \brief End iterator.
             * \return Returns an iterator to the end (i.e. the element after the last element) of the given range.
             */
            Iterator end();

            /*!
             * \brief Reverse begin iterator.
             * \return Returns an iterator to the reverse-beginning of the given range.
             */
            std::reverse_iterator<UrnOR::Iterator> rbegin();

            /*!
             * \brief Reverse begin iterator.
             * \return Returns an iterator to the reverse-end of the given range.
             */
            std::reverse_iterator<UrnOR::Iterator> rend();

            /*!
             * \brief Checks whether the given draw is contained in the urn or not.
             * \return true/false depends if the draw is valid.
             */
            [[nodiscard]] bool valid(const Draw& draw) const;

            /*!
             * \brief Specifies the subsequent draw for the specified draw, if it exists.
             * \return Next draw of type Draw.
             */
            virtual Draw nextDraw(Draw draw) const;

            /*!
             * \brief Specifies the previous draw for the specified draw, if it exists.
             * \return Previous draw of type Draw.
             */
            virtual Draw backDraw(Draw draw) const;

            /*!
             * \brief Calculates the corresponding draw from a given ordinal number.
             * \return Draw of type Draw.
             */
            virtual Draw draw(uint ordinalnumber) const;
      
            /*!
             * \brief Returns the first draw of the urn.
             * \return First draw of type Draw.
             */
            virtual Draw firstDraw() const;

            /*!
             * \brief Returns the last draw of the urn.
             * \return Last draw of type Draw.
             */
            virtual Draw lastDraw() const;

            /*!
             * \brief Virtual destructor for UrnOR.
             * Virtual destructor to be a valid base class.
             * Destructor is defaulted.
             */
            virtual ~UrnOR();
         
        protected:
            const uint m_n, //!< The number of balls inside the urn.
                       m_k; //!< The size of a draw from the urn.
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
             * If the UrnO exemplar to be created is invalid, an exception is thrown.
             * 
             * @param[in] n      The number of balls inside the urn.
             * @param[in] k      The size of a draw from the urn.
             * @param[in] check  The check value.
             */
            explicit UrnO(uint n,uint k,uint check = 2);

            /*!
             * \brief Getter method which returns z.
             * \return z the number of all possible draws.
             */
            virtual uint z() const override;

            /*!
             * \brief Calculates the corresponding draw from a given ordinal number.
             * \return Draw of type Draw.
             */
            virtual Draw draw(uint ordinalnumber) const override;

            /*!
             * \brief Specifies the subsequent draw for the specified draw, if it exists.
             * \return Next draw of type Draw.
             */
            virtual Draw nextDraw(Draw draw) const override;

            /*!
             * \brief Specifies the previous draw for the specified draw, if it exists.
             * \return Previous draw of type Draw.
             */
            virtual Draw backDraw(Draw draw) const override;

            /*!
             * \brief Method to search for duplicate elements.
             * \return true/false depends if the draw is valid.
             */
            bool repetitions(const Draw& repDraw) const;
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
             * \brief Getter method which returns z.
             * \return z the number of all possible draws.
             */
            virtual uint z() const override;

            /*!
             * \brief Calculates the corresponding draw from a given ordinal number.
             * \return Draw of type Draw.
             */
            virtual Draw draw(uint ordinalnumber) const override;

            /*!
             * \brief Specifies the subsequent draw for the specified draw, if it exists.
             * \return Next draw of type Draw.
             */
            virtual Draw nextDraw(Draw draw) const override;

            /*!
             * \brief Specifies the previous draw for the specified draw, if it exists.
             * \return Previous draw of type Draw.
             */
            virtual Draw backDraw(Draw draw) const override;

            /*!
             * \brief Method to check if an element with a lower index value is greater than its neighbor element with index value plus one.
             * \return true/false depends if the draw is valid.
             */
            bool unsorted(const Draw& unsortDraw) const;
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
            explicit Urn(uint n,uint k,uint check = 3);

            /*!
             * \brief Getter method which returns z.
             * \return z the number of all possible draws.
             */
            virtual uint z() const override;

            /*!
             * \brief Calculates the corresponding draw from a given ordinal number.
             * \return Draw of type Draw.
             */
            virtual Draw draw(uint ordinalnumber) const override;

            /*!
             * \brief Specifies the subsequent draw for the specified draw, if it exists.
             * \return Next draw of type Draw.
             */
            virtual Draw nextDraw(Draw draw) const override;

            /*!
             * \brief Specifies the previous draw for the specified draw, if it exists.
             * \return Previous draw of type Draw.
             */
            virtual Draw backDraw(Draw draw) const override;
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
    template<class T, bool ORDER = true, bool REPETITION = true>
    class GenericUrn   
    {   
        public:

            /*!
             * \class Iterator 
             * \brief Iterator which fulfills the requirements as a random access iterator.
             * The behavior is based on the std::vector class. 
             * The special feature of the iterator is that it does not use a memory structure like a vector.
             */

            class Iterator 
            {
                public:
                    using iterator_category = std::random_access_iterator_tag;  /*!< Using decleration for the iterator category which is std::random_access_iterator.*/
                    using difference_type   = std::ptrdiff_t;                   /*!< Using decleration for the difference type which is ptrdiff_t.*/
                    using value_type        = std::vector<T>;                   /*!< Using decleration for the value type which is vector<T>.*/
                    using pointer           = std::vector<T>*;                  /*!< Using decleration for the pointer which is vector<T>*.*/
                    using reference         = const std::vector<T>;             /*!< Using decleration for the reference. The type is const vector<T> due to an error in the standard library when using the std::make_reverse_iterator (http://gcc.gnu.org/PR51823).*/
                    using size_type         = std::size_t;                      /*!< Using decleration for the size type which is size_t.*/

                    /*!
                     * \enum enum class Status
                     * \brief Represents the current status of the iterator.
                     */
                    enum class Status 
                    {
                        invalidFront,
                        valid,
                        invalidBack
                    };
                    
                    /*!
                     * \brief Constructor for Iterator.
                     * Constructs an exampler of Iterator.
                     * @param[in] urn               Pointer to an urn on which the various functions are executed.
                     * @param[in] ordinalnumber     Indicates the ordinal number of a draw.
                     * @param[in] check             Indicates the status of the iterator.
                     */
                    Iterator(const GenericUrn<T, ORDER, REPETITION>* urn, const uint& ordinalnumber, const Status& status);

                    /*!
                     * \brief Standard constructor for Iterator.
                     * Is a requirement for the ranges::random_access_iterator concept.
                     */
                    Iterator();
                    
                    /*!
                     * \brief Getter method which returns the Status of the iterator.
                     * \return Status of iterator as std::string.
                     */
                    std::string status() const;
                    
                    /*!
                     * \brief Getter method which returns n.
                     * \return n the number of balls inside the urn.
                     */
                    uint n() const;

                    /*!
                     * \brief Getter method which returns k.
                     * \return k the size of a draw from the urn.
                     */
                    uint k() const;
    
                    /*!
                     * \brief Getter method which returns z.
                     * \return z the number of all possible draws.
                     */
                    uint z() const;

                    /*!
                     * \brief Getter method which returns ordinalnumber.
                     * \return ordinalnumber the ordinal number of the current draw.
                     */
                    int ordinalnumber() const;
                    
                    /*!
                     * \brief Operator for pointer dereferencing. 
                     * \return Returns the current draw of the iterator as value type.
                     * If the iterator is outside the range, a vector filled with zeros is returned. 
                     */
                    const value_type operator*() const;

                    /*!
                     * \brief Operator for pre-incrementation. 
                     * \return Returns the incremented iterator. 
                     */
                    Iterator& operator++();

                    /*!
                     * \brief Operator for post-incrementation. 
                     * \return Returns the iterator before incrementation. 
                     */
                    Iterator operator++(int);

                    /*!
                     * \brief Operator for pre-decrementation. 
                     * \return Returns the decremented iterator. 
                     */
                    Iterator& operator--();

                    /*!
                     * \brief Operator for post-decrementation. 
                     * \return Returns the iterator before decrementation. 
                     */
                    Iterator operator--(int);

                    /*!
                     * \brief Operator for equal to comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator== (const Iterator& other) const;

                    /*!
                     * \brief Operator for not equal to comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator!= (const Iterator& other) const;

                    /*!
                     * \brief Operator for less than comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator< (const Iterator& other) const;

                    /*!
                     * \brief Operator for greater than comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator> (const Iterator& other) const;

                    /*!
                     * \brief Operator for less than or equal to comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator<=(const Iterator& other) const;

                    /*!
                     * \brief Operator for greater than or equal to comparison. 
                     * \return Returns the evaluated expression. 
                     */
                    bool operator>=(const Iterator& other) const;
    
                    /*!
                     * \brief Operator for addition assignment. 
                     * \return Returns the incremented iterator. 
                     */
                    Iterator& operator+=(const difference_type& other);

                    /*!
                     * \brief Operator for addition. 
                     * \return Returns the sum of iterator and difference type n. 
                     */
                    Iterator operator+(const difference_type& n) const;

                    /*!
                     * \brief Operator for addition (outside class definition). 
                     * \return Returns the sum of iterator and difference type n. 
                     */
                    friend Iterator operator+(const typename GenericUrn<T,ORDER,REPETITION>::Iterator::difference_type& n, const typename GenericUrn<T,ORDER,REPETITION>::Iterator::Iterator& other)
                    {
                        return other + n;
                    }   

                    /*!
                     * \brief Operator for substraction assignment. 
                     * \return Returns the decremented iterator. 
                     */
                    Iterator& operator-=(const difference_type& n);

                    /*!
                     * \brief Operator for substraction. 
                     * \return Returns the difference of iterator and difference type n. 
                     */
                    Iterator operator-(const difference_type& n) const;

                    /*!
                     * \brief Operator for distance. 
                     * \return Returns the distance between the two iterators.
                     */
                    difference_type operator-(const Iterator& other) const;

                    /*!
                     * \brief Operator for index. 
                     * \return Returns the draw to the given index.
                     */
                    reference operator[](size_type index) const;

                    /*!
                     * \brief Destructor for Iterator.
                     * Destructor is defaulted.
                     */
                    ~Iterator();

                protected:
                    const GenericUrn<T, ORDER, REPETITION>* m_itUrn;    //!< Pointer to an urn on which the various functions are executed.
                    int m_ordinalnumber;                                //!< Indicates the ordinal number of a draw.
                    Status m_status;                                    //!< Indicates the status of the iterator
            };

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
            GenericUrn(uint k, const std::vector<T>& elements);

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
             * \brief Getter method which returns z.
             * \return z the number of all possible draws.
             */
            uint z() const;

            /*!
             * \brief Begin iterator.
             * \return Returns an iterator pointing to the first element in the sequence.
             */
            Iterator begin();

            /*!
             * \brief End iterator.
             * \return Returns an iterator to the end (i.e. the element after the last element) of the given range.
             */
            Iterator end();

            /*!
             * \brief Reverse begin iterator.
             * \return Returns an iterator to the reverse-beginning of the given range.
             */
            std::reverse_iterator<GenericUrn<T,ORDER,REPETITION>::Iterator> rbegin();

            /*!
             * \brief Reverse begin iterator.
             * \return Returns an iterator to the reverse-end of the given range.
             */
            std::reverse_iterator<GenericUrn<T,ORDER,REPETITION>::Iterator> rend();

            /*!
             * \brief Converts the draw of type vector<uint> to the elements of type vector<T>. 
             * \return Returns the elemetns of the GenericUrn of type vector<T>.
             */
            std::vector<T> to_element(const Draw& draw) const;

            /*!
             * \brief Specifies the subsequent draw for the specified draw, if it exists.
             * \return Next draw of type vector<T>.
             */
            auto draw(uint ordinalnumber) const;

            /*!
             * \brief Specifies the previous draw for the specified draw, if it exists.
             * \return Previous draw of type vector<T>.
             */
            auto nextDraw(const std::vector<T>& draw) const;

            /*!
             * \brief Call the associated draw() function of the specified urn.
             * \return Draw of type vector<T>.
             */
            auto backDraw(const std::vector<T>& draw) const;

            /*!
             * \brief Returns the first draw of the urn.
             * \return First draw of type vector<T>.
             */
            auto firstDraw();

            /*!
             * \brief Returns the last draw of the urn.
             * \return Last draw of type vector<T>.
             */
            auto lastDraw();

        private:
            using UrnType = typename UrnSelector<ORDER,REPETITION>::UrnType;    /*!< Using decleration as alias for the urn types. */
            UrnType m_urn;                                                      /*!< Exampler of an urn of type UrnType. */
            std::vector<T> m_elements;                                          /*!< Vector of type T containing the different elements inside the urn. */
    };

    /*!
     * Include guard for definitions.tpp
     * definitions.tpp contains the definitions of the class/function templates
     */
    #if __has_include("newdefinitions.tpp")
    #include "newdefinitions.tpp"
    #endif //__has_include
}   
#endif // URN_HPP
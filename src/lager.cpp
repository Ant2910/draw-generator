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
                    const /*value_type*/ std::vector<T> operator*() const; 
                    
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
                    /*reference*/ const std::vector<T> operator[](size_type index) const; 

                    /*!
                     * \brief Destructor for Iterator.
                     * Destructor is defaulted.
                     */
                    ~Iterator();

                protected:
                    const GenericUrn<T,ORDER,REPETITION>* m_itUrn;  //!< Pointer to an urn on which the various functions are executed.
                    int m_ordinalnumber;                            //!< Indicates the ordinal number of a draw.
                    Status m_status;                                //!< Indicates the status of the iterator
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
                auto rbegin();

                /*!
                 * \brief Reverse begin iterator.
                 * \return Returns an iterator to the reverse-end of the given range.
                 */
                auto rend();

                /*!
                 * \brief Converts the draw of type vector<uint> to the elements of type vector<T>. 
                 * \return Returns the elemetns of the GenericUrn of type vector<T>.
                 */
                std::vector<T> to_element(const Draw& draw) const;

                /*!
                 * \brief Specifies the subsequent draw for the specified draw, if it exists.
                 * \return Next draw of type vector<T>.
                 */
                auto nextDraw(const std::vector<T>& draw) const;

                /*!
                 * \brief Specifies the previous draw for the specified draw, if it exists.
                 * \return Previous draw of type vector<T>.
                 */
                auto backDraw(const std::vector<T>& draw) const;

                /*!
                 * \brief Call the associated draw() function of the specified urn.
                 * \return Draw of type vector<T>.
                 */
                auto draw(uint ordinalnumber) const;
      
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

    //Attention: The designations given may differ depending on the source.
    template <class T> // According to https://en.wikipedia.org/wiki/Permutation
    using Permutation = GenericUrn<T,true,true>;          /*!< Using decleration as alias for a GenericUrn of UrnType UrnOR. */

    template <class T> // According to https://en.wikipedia.org/wiki/Partial_permutation
    using PartialPermutation = GenericUrn<T,true,false>;  /*!< Using decleration as alias for a GenericUrn of UrnType UrnO. */

    template <class T> // According to https://en.wikipedia.org/wiki/Combination
    using MultiCombination = GenericUrn<T,false,true>;    /*!< Using decleration as alias for a GenericUrn of UrnType UrnR. */

    template <class T> // According to https://en.wikipedia.org/wiki/Combination
    using Combination = GenericUrn<T,false,false>;        /*!< Using decleration as alias for a GenericUrn of UrnType Urn. */

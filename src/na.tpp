
template <bool O, bool R>
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

template<class T, bool ORDER, bool REPETITION>
GenericUrn<T, ORDER, REPETITION>::GenericUrn(uint k, const std::vector<T>& elements)
    : m_urn(static_cast<uint>(elements.size()), k), m_elements(elements) {}

template<class T, bool ORDER, bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::n() const {
    return m_urn.n();
}

template<class T, bool ORDER, bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::k() const {
    return m_urn.k();
}

template<class T, bool ORDER, bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::z() const {
    return m_urn.z();
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator GenericUrn<T, ORDER, REPETITION>::begin() {
    return Iterator(this, 0, Iterator::Status::valid);
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator GenericUrn<T, ORDER, REPETITION>::end() {
    return Iterator(this, z(), Iterator::Status::invalidBack);
}

template<class T, bool ORDER, bool REPETITION>
auto GenericUrn<T, ORDER, REPETITION>::rbegin() {
    return std::make_reverse_iterator(end());
}

template<class T, bool ORDER, bool REPETITION>
auto GenericUrn<T, ORDER, REPETITION>::rend() {
    return std::make_reverse_iterator(begin());
}

// Implementation of other member functions...

template<class T, bool ORDER, bool REPETITION>
GenericUrn<T, ORDER, REPETITION>::Iterator::Iterator(const GenericUrn<T, ORDER, REPETITION>* urn, const uint& ordinalnumber, const Status& status)
    : m_itUrn{urn}, m_ordinalnumber(static_cast<int>(ordinalnumber)), m_status{status} {}

template<class T, bool ORDER, bool REPETITION>
string GenericUrn<T, ORDER, REPETITION>::Iterator::status() const {
    switch(m_status) {
        case Status::invalidFront: return "invalidFront"; break;
        case Status::valid: return "valid"; break;
        case Status::invalidBack: return "invalidBack"; break;
        default: throw std::invalid_argument("m_status is invalid."); break;
    }
}

template<class T, bool ORDER, bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::Iterator::n() const {
    return (*m_itUrn).n();
}

template<class T, bool ORDER, bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::Iterator::k() const {
    return (*m_itUrn).k();
}

template<class T, bool ORDER, bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::Iterator::z() const {
    return (*m_itUrn).z();
}

template<class T, bool ORDER, bool REPETITION>
int GenericUrn<T, ORDER, REPETITION>::Iterator::ordinalnumber() const {
    return m_ordinalnumber;
}

template<class T, bool ORDER, bool REPETITION>
const typename GenericUrn<T, ORDER, REPETITION>::Iterator::value_type GenericUrn<T, ORDER, REPETITION>::Iterator::operator*() const {
    if(m_ordinalnumber >= z() || m_ordinalnumber < 0) {
        throw std::domain_error("There is no valid draw for this ordinalnumber.");
    }
    return (*m_itUrn).draw(m_ordinalnumber);
}

// Implementation of other operators and member functions...

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator& GenericUrn<T, ORDER, REPETITION>::Iterator::operator++() {
    ++m_ordinalnumber;
    
    if(m_ordinalnumber == 0) {
        m_status = Status::valid;
    }
    else if(m_ordinalnumber < 0) {
        m_status = Status::invalidFront;
    }
    else if(m_ordinalnumber >= z()) {
        m_status = Status::invalidBack;
    }
    
    return *this;
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator GenericUrn<T, ORDER, REPETITION>::Iterator::operator++(int) {
    auto temp {*this};
    ++(*this);
    return temp;
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator& GenericUrn<T, ORDER, REPETITION>::Iterator::operator--() {
    --m_ordinalnumber;
    if(m_ordinalnumber == z()-1) {
        m_status = Status::valid;
    }
    else if(m_ordinalnumber < 0) {
        m_status = Status::invalidFront;
    }
    else if(m_ordinalnumber >= z()) {
        m_status = Status::invalidBack;
    }
    return *this;
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator GenericUrn<T, ORDER, REPETITION>::Iterator::operator--(int) {
    auto temp {*this};
    --(*this);
    return temp;
}

template<class T, bool ORDER, bool REPETITION>
bool GenericUrn<T, ORDER, REPETITION>::Iterator::operator== (const Iterator& other) const {
    return (m_ordinalnumber == other.m_ordinalnumber);
}

template<class T, bool ORDER, bool REPETITION>
bool GenericUrn<T, ORDER, REPETITION>::Iterator::operator!= (const Iterator& other) const {
    return !(*this == other);
}

template<class T, bool ORDER, bool REPETITION>
bool GenericUrn<T, ORDER, REPETITION>::Iterator::operator< (const Iterator& other) const {
    return (m_ordinalnumber < other.m_ordinalnumber);
}

template<class T, bool ORDER, bool REPETITION>
bool GenericUrn<T, ORDER, REPETITION>::Iterator::operator> (const Iterator& other) const {
    return (m_ordinalnumber > other.m_ordinalnumber);
}

template<class T, bool ORDER, bool REPETITION>
bool GenericUrn<T, ORDER, REPETITION>::Iterator::operator<= (const Iterator& other) const {
    return (*this == other || *this < other);
}

template<class T, bool ORDER, bool REPETITION>
bool GenericUrn<T, ORDER, REPETITION>::Iterator::operator>= (const Iterator& other) const {
    return (*this == other || *this > other);
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator& GenericUrn<T, ORDER, REPETITION>::Iterator::operator+=(const difference_type& other) {
    if(other >= 0) {
        for(uint incCount{}; incCount < other; ++incCount) {
            ++(*this);
        }
    }
    else if(other < 0) {   
        long int positivOther {other * -1};
        for(uint decCount{}; decCount < positivOther; ++decCount) {
            --(*this);
        }
    }
    return *this;
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator GenericUrn<T, ORDER, REPETITION>::Iterator::operator+(const difference_type& n) const {
    auto temp {*this};
    return (temp += n);
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator operator+(const typename GenericUrn<T, ORDER, REPETITION>::Iterator::difference_type& n, const typename GenericUrn<T, ORDER, REPETITION>::Iterator& other) {
    return other + n;
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator& GenericUrn<T, ORDER, REPETITION>::Iterator::operator-=(const difference_type& n) {
    long int negativ {n * -1};
    (*this) += negativ;
    return *this;
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator GenericUrn<T, ORDER, REPETITION>::Iterator::operator-(const difference_type& n) const {
    auto temp {*this};
    return (temp -= n);
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator::difference_type GenericUrn<T, ORDER, REPETITION>::Iterator::operator-(const Iterator& other) const {
    return m_ordinalnumber - other.m_ordinalnumber;
}

template<class T, bool ORDER, bool REPETITION>
typename GenericUrn<T, ORDER, REPETITION>::Iterator::reference GenericUrn<T, ORDER, REPETITION>::Iterator::operator[](size_type index) const {
    if(index >= z() || index < 0) {
        throw std::domain_error("There is no valid draw for this ordinalnumber.");
    }
    return (*m_itUrn).draw(index);
}

template<class T, bool ORDER, bool REPETITION>
GenericUrn<T, ORDER, REPETITION>::Iterator::~Iterator() = default;

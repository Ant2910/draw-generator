template <typename T, bool ORDER, bool REPETITION>
GenericUrn<T, ORDER, REPETITION>::It::It(T a) : m_a(a) {}

template <typename T, bool ORDER, bool REPETITION>
GenericUrn<T, ORDER, REPETITION>::GenericUrn(T i) : m_i(i) {}

template <typename T, bool ORDER, bool REPETITION>
T GenericUrn<T, ORDER, REPETITION>::output() const
{
    return m_i;
}

template <typename T, bool ORDER, bool REPETITION>
GenericUrn<T,ORDER,REPETITION>::It GenericUrn<T,ORDER,REPETITION>::It::operator++()
{
    return It{2};
}


template<typename T>
sge::plugin::iterator<T>::iterator(
	category_array::iterator const it)
: it(it)
{}

template<typename T>
void sge::plugin::iterator<T>::advance(const difference_type diff)
{
	it+=diff;
}

template<typename T>
void sge::plugin::iterator<T>::increment()
{
	++it;
}

template<typename T>
void sge::plugin::iterator<T>::decrement()
{
	--it;
}

template<typename T>
bool sge::plugin::iterator<T>::equal(const iterator& r) const
{
	return it == r.it;
}

template<typename T>
typename sge::plugin::iterator<T>::reference
sge::plugin::iterator<T>::dereference() const
{
	return context<T>(**it);
}

template<typename T>
typename sge::plugin::iterator<T>::difference_type
sge::plugin::iterator<T>::distance_to(
	iterator const &r) const
{
	return r.it - it;
}

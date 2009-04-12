#ifndef SGE_ALGORITHM_DETAIL_PTR_CONTAINER_ERASE_IMPL_HPP_INCLUDED
#define SGE_ALGORITHM_DETAIL_PTR_CONTAINER_ERASE_IMPL_HPP_INCLUDED

template<
	typename Container,
	typename Ptr>
void sge::algorithm::ptr_container_erase(
	Container &c,
	Ptr const s)
{
	for (
		typename Container::iterator b = c.begin();
		b != c.end(); 
		++b)
	{
		if (&(*b) != s)
			continue;
		c.erase(b);
		break;
	}
}

#endif

#ifndef SGE_ASSIGN_DETAIL_MAKE_CONTAINER_IMPL_HPP_INCLUDED
#define SGE_ASSIGN_DETAIL_MAKE_CONTAINER_IMPL_HPP_INCLUDED

template<typename Container>
sge::assign::make_container<Container>::make_container(
	typename container_type::const_reference r)
{
	c_.push_back(r);
}

template<typename Container>
sge::assign::make_container<Container> &
	sge::assign::make_container<Container>::operator()(
		typename container_type::const_reference r)
{
	c_.push_back(r);
	return *this;
}

template<typename Container>
sge::assign::make_container<Container>::operator Container() const
{
	return c_;
}

#endif

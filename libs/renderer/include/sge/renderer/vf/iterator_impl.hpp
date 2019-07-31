//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/iterator_decl.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/back.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Part,
	typename Constness
>
typename sge::renderer::vf::iterator<
	Part,
	Constness
>::difference_type
sge::renderer::vf::iterator<
	Part,
	Constness
>::stride()
{
	return
		fcppt::cast::to_signed(
			brigand::back<
				typename Part::offsets
			>::type::value
		);
}

template<
	typename Part,
	typename Constness
>
sge::renderer::vf::iterator<
	Part,
	Constness
>::iterator(
	internal_pointer const _data
)
:
	data_(
		_data
	)
{
}

template<
	typename Part,
	typename Constness
>
void
sge::renderer::vf::iterator<
	Part,
	Constness
>::advance(
	difference_type const _diff
)
{
	data_ +=
		this->stride() * _diff;
}

template<
	typename Part,
	typename Constness
>
void
sge::renderer::vf::iterator<
	Part,
	Constness
>::increment()
{
	data_ +=
		this->stride();
}

template<
	typename Part,
	typename Constness
>
void
sge::renderer::vf::iterator<
	Part,
	Constness
>::decrement()
{
	data_ -=
		this->stride();
}

template<
	typename Part,
	typename Constness
>
bool
sge::renderer::vf::iterator<
	Part,
	Constness
>::equal(
	iterator const &_other
) const
{
	return
		data_ == _other.data_;
}

template<
	typename Part,
	typename Constness
>
typename
sge::renderer::vf::iterator<
	Part,
	Constness
>::difference_type
sge::renderer::vf::iterator<
	Part,
	Constness
>::distance_to(
	iterator const &_other
) const
{
	return
		(_other.data_ - data_)
		/
		stride();
}

template<
	typename Part,
	typename Constness
>
typename
sge::renderer::vf::iterator<
	Part,
	Constness
>::vertex_type
sge::renderer::vf::iterator<
	Part,
	Constness
>::dereference() const
{
	return
		vertex_type(
			data_
		);
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/renderer/index/const_proxy_impl.hpp>
#include <sge/renderer/index/iterator_decl.hpp>
#include <sge/renderer/index/proxy_impl.hpp>
#include <fcppt/cast/to_signed.hpp>


template<
	typename Format
>
sge::renderer::index::iterator<
	Format
>::iterator(
	pointer const _data
)
:
	data_(
		_data
	)
{
}

template<
	typename Format
>
typename sge::renderer::index::iterator<
	Format
>::pointer
sge::renderer::index::iterator<
	Format
>::data() const
{
	return
		data_;
}

template<
	typename Format
>
void
sge::renderer::index::iterator<
	Format
>::advance(
	difference_type const _diff
)
{
	data_ +=
		_diff
		*
		fcppt::cast::to_signed(
			sizeof(
				value_type
			)
		);
}

template<
	typename Format
>
void
sge::renderer::index::iterator<
	Format
>::increment()
{
	this->advance(
		1
	);
}

template<
	typename Format
>
void
sge::renderer::index::iterator<
	Format
>::decrement()
{
	this->advance(
		-1
	);
}

template<
	typename Format
>
bool
sge::renderer::index::iterator<
	Format
>::equal(
	iterator const &_other
) const
{
	return
		data_
		==
		_other.data_;
}

template<
	typename Format
>
typename
sge::renderer::index::iterator<
	Format
>::difference_type
sge::renderer::index::iterator<
	Format
>::distance_to(
	iterator const &_other
) const
{
	return
		(
			_other.data_
			-
			data_
		)
		/
		fcppt::cast::to_signed(
			sizeof(
				value_type
			)
		);
}

template<
	typename Format
>
typename
sge::renderer::index::iterator<
	Format
>::reference
sge::renderer::index::iterator<
	Format
>::dereference() const
{
	return
		reference(
			data_
		);
}

#endif

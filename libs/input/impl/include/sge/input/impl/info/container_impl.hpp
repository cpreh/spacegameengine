//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_IMPL_INFO_CONTAINER_IMPL_HPP_INCLUDED
#define SGE_INPUT_IMPL_INFO_CONTAINER_IMPL_HPP_INCLUDED

#include <sge/input/info/container.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Id,
	typename Obj
>
sge::input::info::container<
	Id,
	Obj
>::container(
	vector &&_vector
)
:
	vector_(
		std::move(
			_vector
		)
	)
{
}

template<
	typename Id,
	typename Obj
>
Obj const &
sge::input::info::container<
	Id,
	Obj
>::operator[](
	Id const &_id
) const
{
	return
		vector_[
			_id.get()
		];
}

template<
	typename Id,
	typename Obj
>
Id
sge::input::info::container<
	Id,
	Obj
>::size() const
{
	return
		Id(
			fcppt::cast::size<
				typename Id::value_type
			>(
				vector_.size()
			)
		);
}

template<
	typename Id,
	typename Obj
>
bool
sge::input::info::container<
	Id,
	Obj
>::empty() const
{
	return
		vector_.size()
		==
		0u;
}

template<
	typename Id,
	typename Obj
>
typename sge::input::info::container<
	Id,
	Obj
>::vector const &
sge::input::info::container<
	Id,
	Obj
>::get() const
{
	return
		vector_;
}

#endif

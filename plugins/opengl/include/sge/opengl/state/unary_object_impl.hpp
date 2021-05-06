//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_UNARY_OBJECT_IMPL_HPP_INCLUDED
#define SGE_OPENGL_STATE_UNARY_OBJECT_IMPL_HPP_INCLUDED

#include <sge/opengl/state/unary_object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Base,
	typename Parameter
>
sge::opengl::state::unary_object<
	Base,
	Parameter
>::unary_object(
	actor_vector &&_actors
)
:
	actors_(
		std::move(
			_actors
		)
	)
{
}

namespace sge::opengl::state
{
template<
	typename Base,
	typename Parameter
>
unary_object<
	Base,
	Parameter
>::~unary_object()
= default;
}

template<
	typename Base,
	typename Parameter
>
void
sge::opengl::state::unary_object<
	Base,
	Parameter
>::set(
	Parameter const &_parameter
) const
{
	for(
		actor_type const &actor
		:
		actors_
	)
	{
		actor(
			_parameter
		);
	}
}

#endif

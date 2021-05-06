//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_OPENGL_STATE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Base
>
sge::opengl::state::object<
	Base
>::object(
	sge::opengl::state::actor_vector &&_actors
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
	typename Base
>
object<
	Base
>::~object()
= default;
}

template<
	typename Base
>
void
sge::opengl::state::object<
	Base
>::set() const
{
	for(
		sge::opengl::state::actor const &cur
		:
		this->actors_
	)
	{
		cur();
	}
}

#endif

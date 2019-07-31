//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_OPENGL_STATE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/object.hpp>


template<
	typename Base
>
sge::opengl::state::object<
	Base
>::object(
	sge::opengl::state::actor_vector const &_actors
)
:
	actors_(
		_actors
	)
{
}

template<
	typename Base
>
sge::opengl::state::object<
	Base
>::~object()
{
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
		sge::opengl::state::actor_vector::const_iterator it(
			actors_.begin()
		);
		it != actors_.end();
		++it
	)
		(*it)();
}

#endif

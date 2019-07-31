//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CONTEXT_USE_IMPL_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_USE_IMPL_HPP_INCLUDED

#include <sge/opengl/context/base_fwd.hpp>
#include <sge/opengl/context/make_object.hpp>
#include <sge/opengl/context/object.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/from.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

template<
	typename Type,
	typename Parameter
>
Type &
use_impl(
	sge::opengl::context::object &_object,
	Parameter &&_parameter
)
{
	return
		fcppt::cast::static_downcast<
			Type &
		>(
			fcppt::optional::from(
				_object.get(
					Type::static_id
				),
				[
					&_object,
					&_parameter
				]()
				{
					return
						fcppt::make_ref(
							_object.insert(
								Type::static_id,
								sge::opengl::context::make_object<
									Type
								>(
									_parameter
								)
							)
						);
				}
			).get()
		);
}

}
}
}

#endif

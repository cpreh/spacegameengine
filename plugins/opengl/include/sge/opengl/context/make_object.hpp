//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CONTEXT_MAKE_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_MAKE_OBJECT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/base_unique_ptr.hpp>
#include <sge/opengl/context/dummy_parameter_fwd.hpp>
#include <sge/opengl/context/has_parameter.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/not.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

template<
	typename Type
>
std::enable_if_t<
	sge::opengl::context::has_parameter<
		Type
	>::value,
	sge::opengl::context::base_unique_ptr
>
make_object(
	typename
	Type::parameter &_parameter
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::context::base
		>(
			fcppt::make_unique_ptr<
				Type
			>(
				_parameter
			)
		);
}

template<
	typename Type
>
std::enable_if_t<
	fcppt::not_(
		sge::opengl::context::has_parameter<
			Type
		>::value
	),
	sge::opengl::context::base_unique_ptr
>
make_object(
	sge::opengl::context::dummy_parameter const &
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::context::base
		>(
			fcppt::make_unique_ptr<
				Type
			>(
			)
		);
}

}
}
}

#endif

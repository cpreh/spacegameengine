//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_MAKE_HARDWARE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_MAKE_HARDWARE_HPP_INCLUDED

#include <sge/opengl/buffer/base_unique_ptr.hpp>
#include <sge/opengl/buffer/hardware.hpp>
#include <sge/opengl/buffer/hardware_config_fwd.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

template<
	typename... Args
>
std::array<
	sge::opengl::buffer::base_unique_ptr,
	sizeof...(Args)
>
make_hardware(
	sge::opengl::buffer::hardware_config const &_config,
	Args const ..._args
)
{
	return
		std::array<
			sge::opengl::buffer::base_unique_ptr,
			sizeof...(Args)
		>{{
			fcppt::unique_ptr_to_base<
				sge::opengl::buffer::base
			>(
				fcppt::make_unique_ptr<
					sge::opengl::buffer::hardware
				>(
					fcppt::strong_typedef_construct_cast<
						sge::opengl::buffer::type,
						fcppt::cast::static_cast_fun
					>(
						_args
					),
					_config
				)
			)...
		}};
}

}
}
}

#endif

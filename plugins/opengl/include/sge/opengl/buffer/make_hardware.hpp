//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_MAKE_HARDWARE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_MAKE_HARDWARE_HPP_INCLUDED

#include <sge/opengl/buffer/base_unique_ptr.hpp>
#include <sge/opengl/buffer/const_hardware_config_ref.hpp>
#include <sge/opengl/buffer/hardware.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/cast/static_cast_fun.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

template<
	typename... Args
>
fcppt::array::object<
	sge::opengl::buffer::base_unique_ptr,
	sizeof...(Args)
>
make_hardware(
	sge::opengl::buffer::const_hardware_config_ref const _config,
	Args const ..._args
)
{
	return
		fcppt::array::object<
			sge::opengl::buffer::base_unique_ptr,
			sizeof...(Args)
		>{
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
		};
}

}
}
}

#endif

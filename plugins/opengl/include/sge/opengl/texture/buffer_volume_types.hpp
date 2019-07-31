//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BUFFER_VOLUME_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BUFFER_VOLUME_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/buffer_volume_types_fwd.hpp>
#include <sge/opengl/texture/init_function.hpp>
#include <sge/opengl/texture/sub_function.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/math/size_type.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

struct buffer_volume_types
{
	static
	sge::renderer::size_type
	min_size();

	static constexpr fcppt::math::size_type const num_dims = 3;

	typedef
	sge::opengl::texture::init_function<
		num_dims
	>
	init_function_type;

	static
	init_function_type
	init_function();

	typedef
	sge::opengl::texture::sub_function<
		num_dims
	>
	sub_function_type;

	static
	sub_function_type
	sub_function();
};

}
}
}

#endif

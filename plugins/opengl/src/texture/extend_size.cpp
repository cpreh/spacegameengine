//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/extend_size.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/math/dim/fill.hpp>


sge::renderer::dim2
sge::opengl::texture::extend_size(
	sge::renderer::size_type const _border_size
)
{
	return
		fcppt::math::dim::fill<
			sge::renderer::dim2
		>(
			_border_size
		);
}

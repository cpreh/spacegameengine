//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/create_planar.hpp>
#include <sge/opengl/texture/planar.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::texture::planar_unique_ptr
sge::opengl::texture::create_planar(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::planar_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::texture::planar
		>(
			fcppt::make_unique_ptr<
				sge::opengl::texture::planar
			>(
				_basic_parameters,
				_parameters
			)
		);
}

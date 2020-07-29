//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/volume.hpp>
#include <sge/opengl/texture/volume_config.hpp>
#include <sge/opengl/texture/volume_types.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>


sge::opengl::texture::volume::volume(
	sge::opengl::texture::volume_config const &_config,
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::volume_parameters const &_parameters
)
:
	sge::opengl::texture::volume_basic(
		_basic_parameters,
		_config.volume_texture_type(),
		_parameters,
		_config
	)
{
}

sge::opengl::texture::volume::~volume()
= default;

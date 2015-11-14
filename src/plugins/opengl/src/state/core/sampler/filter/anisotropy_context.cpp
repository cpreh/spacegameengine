/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_config.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context.hpp>
#include <sge/opengl/state/core/sampler/filter/optional_anisotropy_config.hpp>


sge::opengl::state::core::sampler::filter::anisotropy_context::anisotropy_context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	config_(
		sge::opengl::info::extension_supported(
			_info.extensions(),
			sge::opengl::info::extension{
				"GL_EXT_texture_filter_anisotropic"
			}
		)
		?
			sge::opengl::state::core::sampler::filter::optional_anisotropy_config(
				sge::opengl::state::core::sampler::filter::anisotropy_config(
					sge::opengl::convert::to_gl_enum<
						GL_TEXTURE_MAX_ANISOTROPY_EXT
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
					>()
				)
			)
		:
			sge::opengl::state::core::sampler::filter::optional_anisotropy_config()
	)
{
}

sge::opengl::state::core::sampler::filter::anisotropy_context::~anisotropy_context()
{
}

sge::opengl::state::core::sampler::filter::optional_anisotropy_config const &
sge::opengl::state::core::sampler::filter::anisotropy_context::config() const
{
	return
		config_;
}

sge::opengl::context::id const
sge::opengl::state::core::sampler::filter::anisotropy_context::static_id(
	sge::opengl::context::make_id()
);

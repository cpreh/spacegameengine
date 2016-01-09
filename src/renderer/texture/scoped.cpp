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


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/make_cref.hpp>


sge::renderer::texture::scoped::scoped(
	sge::renderer::context::core &_context,
	sge::renderer::texture::base const &_texture,
	sge::renderer::texture::stage const _stage
)
:
	context_(
		_context
	),
	stage_(
		_stage
	)
{
	context_.texture(
		sge::renderer::texture::const_optional_base_ref(
			fcppt::make_cref(
				_texture
			)
		),
		stage_
	);
}

sge::renderer::texture::scoped::~scoped()
{
	context_.texture(
		sge::renderer::texture::const_optional_base_ref(),
		stage_
	);
}

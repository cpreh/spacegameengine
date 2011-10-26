/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/texture/filter/set.hpp>
#include <sge/opengl/texture/filter/visitor.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/scoped_work_bind.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/filter/need_mipmap.hpp>
#include <sge/renderer/texture/filter/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


void
sge::opengl::texture::filter::set(
	opengl::context::object &_context,
	opengl::texture::base const &_texture,
	renderer::stage const _stage,
	renderer::texture::filter::object const &_filter
)
{
	if(
		!_texture.update_filter(
			_filter
		)
	)
		return;

	if(
		sge::renderer::texture::filter::need_mipmap(
			_filter
		)
		&&
		!_texture.has_mipmap()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Mipmap filter used with a texture that has none!")
		);

	opengl::texture::scoped_work_bind const binding(
		_context,
		_texture.type(),
		_texture.id(),
		_stage
	);

	fcppt::variant::apply_unary(
		filter::visitor(
			_context,
			binding,
			_texture.type()
		),
		_filter.variant()
	);
}

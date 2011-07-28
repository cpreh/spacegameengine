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


#include "../set_filter.hpp"
#include "../filter_visitor.hpp"
#include "../../base.hpp"
#include "../../scoped_work_bind.hpp"
#include <sge/renderer/texture/filter/object.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>

void
sge::opengl::texture::funcs::set_filter(
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

	opengl::texture::scoped_work_bind const binding(
		_context,
		_texture.type(),
		_texture.id(),
		_stage
	);

	fcppt::variant::apply_unary(
		funcs::filter_visitor(
			_context,
			binding,
			_texture.type()
		),
		_filter.variant()
	);
}

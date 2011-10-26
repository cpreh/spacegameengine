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


#include <sge/opengl/texture/filter/visitor.hpp>
#include <sge/opengl/texture/filter/anisotropic.hpp>
#include <sge/opengl/texture/filter/normal.hpp>

sge::opengl::texture::filter::visitor::visitor(
	opengl::context::object &_context,
	texture::scoped_work_bind const &_scoped_work,
	texture::type const _type
)
:
	context_(_context),
	scoped_work_(_scoped_work),
	type_(_type)
{
}

sge::opengl::texture::filter::visitor::result_type
sge::opengl::texture::filter::visitor::operator()(
	sge::renderer::texture::filter::anisotropic::object const &_filter
) const
{
	filter::anisotropic(
		context_,
		scoped_work_,
		type_,
		_filter
	);
}

sge::opengl::texture::filter::visitor::result_type
sge::opengl::texture::filter::visitor::operator()(
	sge::renderer::texture::filter::normal::object const &_filter
) const
{
	filter::normal(
		context_,
		scoped_work_,
		type_,
		_filter
	);
}

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/filter/anisotropic.hpp>
#include <sge/opengl/texture/filter/normal.hpp>
#include <sge/opengl/texture/filter/visitor.hpp>
#include <sge/renderer/texture/filter/anisotropic/object_fwd.hpp>
#include <sge/renderer/texture/filter/normal/object_fwd.hpp>


sge::opengl::texture::filter::visitor::visitor(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::type const _type
)
:
	system_context_(
		_system_context
	),
	binding_(
		_binding
	),
	type_(
		_type
	)
{
}

sge::opengl::texture::filter::visitor::result_type
sge::opengl::texture::filter::visitor::operator()(
	sge::renderer::texture::filter::anisotropic::object const &_filter
) const
{
	sge::opengl::texture::filter::anisotropic(
		system_context_,
		binding_,
		type_,
		_filter
	);
}

sge::opengl::texture::filter::visitor::result_type
sge::opengl::texture::filter::visitor::operator()(
	sge::renderer::texture::filter::normal::object const &_filter
) const
{
	sge::opengl::texture::filter::normal(
		system_context_,
		binding_,
		type_,
		_filter
	);
}

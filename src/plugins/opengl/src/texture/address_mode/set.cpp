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


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/address_mode/context.hpp>
#include <sge/opengl/texture/address_mode/set.hpp>
#include <sge/opengl/texture/convert/address_mode.hpp>
#include <sge/opengl/texture/convert/address_mode_type.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>


namespace
{

template<
	typename Mode,
	typename ContextFun
>
void
update_one(
	sge::opengl::texture::address_mode::context &,
	sge::opengl::texture::binding const &,
	sge::opengl::texture::type,
	sge::renderer::texture::stage,
	ContextFun const &
);

}

void
sge::opengl::texture::address_mode::set(
	sge::opengl::context::object &_context,
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::type const _type,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::address_mode::context &context(
		sge::opengl::context::use<
			sge::opengl::texture::address_mode::context
		>(
			_context
		)
	);

	update_one<
		sge::renderer::texture::address_mode_s
	>(
		context,
		_binding,
		_type,
		_stage,
		&sge::opengl::texture::address_mode::context::get_s
	);

	update_one<
		sge::renderer::texture::address_mode_t
	>(
		context,
		_binding,
		_type,
		_stage,
		&sge::opengl::texture::address_mode::context::get_t
	);

	update_one<
		sge::renderer::texture::address_mode_u
	>(
		context,
		_binding,
		_type,
		_stage,
		&sge::opengl::texture::address_mode::context::get_u
	);
}

namespace
{

template<
	typename Mode,
	typename ContextFun
>
void
update_one(
	sge::opengl::texture::address_mode::context &_context,
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::type const _type,
	sge::renderer::texture::stage const _stage,
	ContextFun const &_context_fun
)
{
	sge::opengl::texture::funcs::parameter_int(
		_binding,
		_type,
		sge::opengl::texture::convert::address_mode_type<
			Mode
		>::get(),
		static_cast<
			GLint
		>(
			sge::opengl::texture::convert::address_mode(
				(
					_context.*_context_fun
				)(
					_stage
				).get()
			)
		)
	);
}

}

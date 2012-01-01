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
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/address_mode/context.hpp>
#include <sge/opengl/texture/address_mode/set.hpp>
#include <sge/opengl/texture/convert/address_mode.hpp>
#include <sge/opengl/texture/convert/address_mode_type.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>
#include <sge/renderer/texture/stage.hpp>


namespace
{

template<
	typename Mode,
	typename ContextFun,
	typename TexFun
>
void
update_one(
	sge::opengl::texture::address_mode::context &,
	sge::opengl::texture::binding const &,
	sge::opengl::texture::base const &,
	sge::renderer::texture::stage,
	ContextFun const &,
	TexFun const &
);

template<
	typename Mode
>
void
set_impl(
	sge::opengl::texture::binding const &,
	sge::opengl::texture::type,
	Mode const &
);

}

void
sge::opengl::texture::address_mode::set(
	sge::opengl::context::object &_context,
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::base const &_texture_base,
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
		_texture_base,
		_stage,
		&sge::opengl::texture::address_mode::context::get_s,
		&sge::opengl::texture::base::update_address_mode_s
	);

	update_one<
		sge::renderer::texture::address_mode_t
	>(
		context,
		_binding,
		_texture_base,
		_stage,
		&sge::opengl::texture::address_mode::context::get_t,
		&sge::opengl::texture::base::update_address_mode_t
	);

	update_one<
		sge::renderer::texture::address_mode_u
	>(
		context,
		_binding,
		_texture_base,
		_stage,
		&sge::opengl::texture::address_mode::context::get_u,
		&sge::opengl::texture::base::update_address_mode_u
	);
}

namespace
{

template<
	typename Mode,
	typename ContextFun,
	typename TexFun
>
void
update_one(
	sge::opengl::texture::address_mode::context &_context,
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::base const &_texture_base,
	sge::renderer::texture::stage const _stage,
	ContextFun const &_context_fun,
	TexFun const &_tex_fun
)
{
	Mode const new_value(
		(
			_context.*_context_fun
		)(
			_stage
		)
	);

	if(
		(
			_texture_base.*_tex_fun
		)(
			new_value
		)
	)
		set_impl(
			_binding,
			_texture_base.type(),
			new_value
		);
}

template<
	typename Mode
>
void
set_impl(
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::type const _type,
	Mode const &_mode
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
				_mode.get()
			)
		)
	);
}

}

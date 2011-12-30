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


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/texture/address_mode/context.hpp>
#include <sge/renderer/texture/address_mode_default.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/container/index_map_impl.hpp>


namespace
{

template<
	typename Mode
>
bool
set_mode_impl(
	sge::renderer::texture::stage,
	Mode,
	fcppt::container::index_map<
		Mode
	> &
);

template<
	typename Mode
>
Mode &
get_mutable_impl(
	sge::renderer::texture::stage,
	fcppt::container::index_map<
		Mode
	> &_map
);

}

sge::opengl::texture::address_mode::context::context()
:
	opengl::context::base(),
	mode_s_(),
	mode_t_(),
	mode_u_()
{
}

sge::opengl::texture::address_mode::context::~context()
{
}

sge::renderer::texture::address_mode_s const &
sge::opengl::texture::address_mode::context::get_s(
	renderer::texture::stage const _stage
)
{
	return
		get_mutable_impl(
			_stage,
			mode_s_
		);
}

sge::renderer::texture::address_mode_t const &
sge::opengl::texture::address_mode::context::get_t(
	renderer::texture::stage const _stage
)
{
	return
		get_mutable_impl(
			_stage,
			mode_t_
		);
}

sge::renderer::texture::address_mode_u const &
sge::opengl::texture::address_mode::context::get_u(
	renderer::texture::stage const _stage
)
{
	return
		get_mutable_impl(
			_stage,
			mode_u_
		);
}

bool
sge::opengl::texture::address_mode::context::set(
	renderer::texture::stage const _stage,
	renderer::texture::address_mode_s const _mode
)
{
	return
		set_mode_impl(
			_stage,
			_mode,
			mode_s_
		);
}

bool
sge::opengl::texture::address_mode::context::set(
	renderer::texture::stage const _stage,
	renderer::texture::address_mode_t const _mode
)
{
	return
		set_mode_impl(
			_stage,
			_mode,
			mode_t_
		);
}

bool
sge::opengl::texture::address_mode::context::set(
	renderer::texture::stage const _stage,
	renderer::texture::address_mode_u const _mode
)
{
	return
		set_mode_impl(
			_stage,
			_mode,
			mode_u_
		);
}

sge::opengl::context::id const
sge::opengl::texture::address_mode::context::static_id(
	sge::opengl::context::make_id()
);

namespace
{

template<
	typename Mode
>
bool
set_mode_impl(
	sge::renderer::texture::stage const _stage,
	Mode const _mode,
	fcppt::container::index_map<
		Mode
	> &_map
)
{
	Mode &current(
		get_mutable_impl(
			_stage,
			_map
		)
	);

	if(
		current
		==
		_mode
	)
		return false;

	current = _mode;

	return true;

}

template<
	typename Mode
>
Mode &
get_mutable_impl(
	sge::renderer::texture::stage const _stage,
	fcppt::container::index_map<
		Mode
	> &_map
)
{
	return
		_map.get_default(
			_stage.get(),
			Mode(
				sge::renderer::texture::address_mode_default()
			)
		);
}

}

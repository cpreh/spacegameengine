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


#include "../context.hpp"
#include "../../../context/make_id.hpp"
#include <sge/renderer/texture/filter/default.hpp>
#include <fcppt/container/index_map_impl.hpp>
#include <fcppt/variant/equal.hpp>

sge::opengl::texture::filter::context::context()
:
	opengl::context::base(),
	filters_()
{
}

sge::opengl::texture::filter::context::~context()
{
}

sge::renderer::texture::filter::object const &
sge::opengl::texture::filter::context::get(
	renderer::stage const _stage
)
{
	return
		this->get_mutable(
			_stage
		);
}

bool
sge::opengl::texture::filter::context::set(
	renderer::stage const _stage,
	renderer::texture::filter::object const &_filter
)
{
	renderer::texture::filter::object &current(
		this->get_mutable(
			_stage
		)
	);

	if(
		current
		==
		_filter
	)
		return false;

	current = _filter;

	return true;
}

sge::renderer::texture::filter::object &
sge::opengl::texture::filter::context::get_mutable(
	renderer::stage const _stage
)
{
	return
		filters_.get_default(
			_stage.get(),
			renderer::texture::filter::default_()
		);
}

sge::opengl::context::id const
sge::opengl::texture::filter::context::static_id(
	sge::opengl::context::make_id()
);

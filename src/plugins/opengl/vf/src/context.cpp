/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../../context/make_id.hpp"
#include <fcppt/container/linear_set_impl.hpp>

sge::opengl::vf::context::context()
:
	state_()
{}

sge::opengl::vf::context::~context()
{
}

sge::opengl::vf::client_state const &
sge::opengl::vf::context::state()
{
	return state_;
}

void
sge::opengl::vf::context::state(
	client_state const &_state
)
{
	state_ = _state;
}

sge::opengl::context::id const
sge::opengl::vf::context::static_id(
	sge::opengl::context::make_id()
);

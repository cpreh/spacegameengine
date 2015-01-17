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


#include <sge/opengl/fbo/bind.hpp>
#include <sge/opengl/fbo/context_fwd.hpp>
#include <sge/opengl/fbo/create_id.hpp>
#include <sge/opengl/fbo/delete_id.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/opengl/fbo/object.hpp>


sge::opengl::fbo::object::object(
	sge::opengl::fbo::context const &_context
)
:
	context_(
		_context
	),
	id_(
		sge::opengl::fbo::create_id(
			context_
		)
	)
{
}

sge::opengl::fbo::object::~object()
{
	sge::opengl::fbo::delete_id(
		context_,
		id_
	);
}

void
sge::opengl::fbo::object::bind() const
{
	sge::opengl::fbo::bind(
		context_,
		this->id()
	);
}

sge::opengl::fbo::id const
sge::opengl::fbo::object::id() const
{
	return id_;
}

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/occlusion_query/context_fwd.hpp>
#include <sge/opengl/occlusion_query/create_id.hpp>
#include <sge/opengl/occlusion_query/delete_id.hpp>
#include <sge/opengl/occlusion_query/holder.hpp>
#include <sge/opengl/occlusion_query/id.hpp>


sge::opengl::occlusion_query::holder::holder(
	sge::opengl::occlusion_query::context const &_context
)
:
	context_(
		_context
	),
	id_(
		sge::opengl::occlusion_query::create_id(
			context_
		)
	)
{
}

sge::opengl::occlusion_query::holder::~holder()
{
	sge::opengl::occlusion_query::delete_id(
		context_,
		id_
	);
}

sge::opengl::occlusion_query::id const
sge::opengl::occlusion_query::holder::id() const
{
	return
		id_;
}

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


#include <sge/model/obj/mesh_sequence.hpp>
#include <sge/model/obj/normal_sequence.hpp>
#include <sge/model/obj/texcoord_sequence.hpp>
#include <sge/model/obj/vertex_sequence.hpp>
#include <sge/src/model/obj/instance_impl.hpp>
#include <sge/src/model/obj/parse.hpp>
#include <sge/src/model/obj/tokens_fwd.hpp>
#include <fcppt/filesystem/path.hpp>


sge::model::obj::instance_impl::instance_impl(
	obj::tokens const &_tokens,
	fcppt::filesystem::path const &_path
)
:
	state_()
{
	obj::parse(
		_tokens,
		_path,
		state_
	);
}

sge::model::obj::instance_impl::~instance_impl()
{
}

sge::model::obj::vertex_sequence const &
sge::model::obj::instance_impl::vertices() const
{
	return state_.vertices_;
}

sge::model::obj::texcoord_sequence const &
sge::model::obj::instance_impl::texcoords() const
{
	return state_.texcoords_;
}

sge::model::obj::normal_sequence const &
sge::model::obj::instance_impl::normals() const
{
	return state_.normals_;
}

sge::model::obj::mesh_sequence const &
sge::model::obj::instance_impl::meshes() const
{
	return state_.meshes_;
}

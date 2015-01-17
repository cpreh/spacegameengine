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


#ifndef SGE_SCENIC_SCENE_ENTITY_HPP_INCLUDED
#define SGE_SCENIC_SCENE_ENTITY_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/scene/mesh_path.hpp>
#include <sge/scenic/scene/position.hpp>
#include <sge/scenic/scene/rotation.hpp>
#include <sge/scenic/scene/scale.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
class entity
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	entity(
		sge::scenic::scene::mesh_path const &,
		sge::scenic::scene::position const &,
		sge::scenic::scene::rotation const &,
		sge::scenic::scene::scale const &);

	SGE_SCENIC_DETAIL_SYMBOL
	entity(
		entity &&
	);

	SGE_SCENIC_DETAIL_SYMBOL
	entity &
	operator=(
		entity &&
	);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::mesh_path const &
	mesh_path() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::position const &
	position() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::rotation const &
	rotation() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::scale const &
	scale() const;

	SGE_SCENIC_DETAIL_SYMBOL
	~entity();
private:
	sge::scenic::scene::mesh_path mesh_path_;
	sge::scenic::scene::position position_;
	sge::scenic::scene::rotation rotation_;
	sge::scenic::scene::scale scale_;
};
}
}
}

#endif

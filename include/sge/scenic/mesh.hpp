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


#ifndef SGE_SCENIC_MESH_HPP_INCLUDED
#define SGE_SCENIC_MESH_HPP_INCLUDED

#include <sge/model/obj/instance_fwd.hpp>
#include <sge/scenic/position.hpp>
#include <sge/scenic/rotation.hpp>
#include <sge/scenic/scale.hpp>
#include <sge/scenic/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace sge
{
namespace scenic
{
class mesh
{
FCPPT_NONCOPYABLE(
	mesh);
public:
	SGE_SCENIC_SYMBOL
	mesh(
		sge::model::obj::instance &,
		sge::scenic::position const &,
		sge::scenic::rotation const &,
		sge::scenic::scale const &);

	SGE_SCENIC_SYMBOL
	sge::model::obj::instance &
	model() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::position const &
	position() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::rotation const &
	rotation() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::scale const &
	scale() const;

	SGE_SCENIC_SYMBOL
	~mesh();
private:
	sge::model::obj::instance &model_;
	sge::scenic::position const position_;
	sge::scenic::rotation const rotation_;
	sge::scenic::scale const scale_;
};
}
}

#endif

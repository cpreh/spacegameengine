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


#ifndef SGE_PROJECTILE_SHAPE_TRIANGLE_MESH_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_TRIANGLE_MESH_HPP_INCLUDED

#include <sge/projectile/scalar.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/shape/base.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


class btCollisionShape;
class btTriangleIndexVertexArray;
class btBvhTriangleMeshShape;

namespace sge
{
namespace projectile
{
namespace shape
{
class triangle_mesh
:
	public sge::projectile::shape::base
{
FCPPT_NONCOPYABLE(
	triangle_mesh);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL explicit
	triangle_mesh(
		shape::triangle_sequence const &);

	// No symbol needed here
	btCollisionShape &
	bullet_shape()
	override;

	btCollisionShape const &
	bullet_shape() const
	override;

	SGE_PROJECTILE_DETAIL_SYMBOL
	~triangle_mesh()
	override;
private:
	typedef
	fcppt::container::raw_vector<int>
	index_vector;

	typedef
	fcppt::container::raw_vector<scalar>
	scalar_vector;

	scalar_vector scalars_;
	index_vector indices_;
	std::unique_ptr<btTriangleIndexVertexArray> mesh_;
	std::unique_ptr<btBvhTriangleMeshShape> bullet_shape_;
};
}
}
}

#endif

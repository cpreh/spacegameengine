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


#ifndef SGE_PROJECTILE_SHAPE_TRIANGLE_MESH_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_TRIANGLE_MESH_HPP_INCLUDED

#include <sge/projectile/scalar.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/projectile/shape/base.hpp>
#include <sge/projectile/shape/triangle_set.hpp>
#include <sge/projectile/symbol.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

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
	public base
{
FCPPT_NONCOPYABLE(
	triangle_mesh);
public:
	SGE_PROJECTILE_SYMBOL explicit
	triangle_mesh(
		triangle_set const &);

	// No symbol needed here
	btCollisionShape &
	bullet_shape();

	btCollisionShape const &
	bullet_shape() const;

	SGE_PROJECTILE_SYMBOL ~triangle_mesh();
private:
	typedef
	fcppt::container::raw_vector<int>
	index_vector;

	typedef
	fcppt::container::raw_vector<scalar>
	scalar_vector;

	scalar_vector scalars_;
	index_vector indices_;
	fcppt::scoped_ptr<btTriangleIndexVertexArray> mesh_;
	fcppt::scoped_ptr<btBvhTriangleMeshShape> bullet_shape_;
};
}
}
}

#endif

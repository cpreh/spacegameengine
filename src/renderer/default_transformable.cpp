/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/default_transformable.hpp>
#include <sge/renderer/device.hpp>
#include <sge/math/matrix_impl.hpp>

sge::renderer::default_transformable::default_transformable(
	device_ptr const rend,
	math::space_matrix const &internal_matrix_,
	math::space_matrix const &projection_,
	math::space_matrix const &transform_)
:
	rend(rend),
	internal_matrix_(internal_matrix_),
	projection_(projection_),
	transform_(transform_)
{}

void sge::renderer::default_transformable::internal_transformation(
	math::space_matrix const &m)
{
	internal_matrix_ = m;
}

void sge::renderer::default_transformable::transform(
	math::space_matrix const &m)
{
	transform_ = m;
}

void sge::renderer::default_transformable::projection(
	math::space_matrix const &m)
{
	projection_ = m;
}

void sge::renderer::default_transformable::set_matrices()
{
	rend->transform(transform_ * internal_matrix_);
	rend->projection(projection_);
}

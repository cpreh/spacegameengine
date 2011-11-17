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


#include <sge/camera/projection/to_matrix.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/perspective_af.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace
{
class conversion_operator
{
public:
	typedef
	sge::renderer::matrix4
	result_type;

	sge::renderer::matrix4 const
	operator()(sge::camera::projection::orthogonal const &ortho) const
	{
		return
			sge::renderer::projection::orthogonal(
				ortho.rect(),
				sge::renderer::projection::near(
					ortho.near()),
				sge::renderer::projection::far(
					ortho.far()));
	}

	sge::renderer::matrix4 const
	operator()(sge::camera::projection::perspective const &o) const
	{
		return
			sge::renderer::projection::perspective_af(
				o.aspect(),
				o.fov(),
				o.near(),
				o.far()
			);
	}
};
}

sge::renderer::matrix4 const
sge::camera::projection::to_matrix(
	object const &o)
{
	if (o.empty())
		return fcppt::math::matrix::scaling<renderer::scalar>(0, 0, 0);
	return
		fcppt::variant::apply_unary(
			conversion_operator(),
			o);
}

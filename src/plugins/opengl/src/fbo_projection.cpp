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


#include "../fbo_projection.hpp"
#include <sge/math/matrix/scaling.hpp>
#include <sge/math/matrix/arithmetic.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

namespace
{

class multiply_visitor
: public boost::static_visitor<
	sge::renderer::any_matrix
> {
public:
	template<
		typename T
	>
	sge::renderer::any_matrix const
	operator()(
		T const &t) const;
};

}

sge::renderer::any_matrix const
sge::ogl::fbo_projection(
	renderer::any_matrix const &m)
{
	return boost::apply_visitor(
		multiply_visitor(),
		m);
}

namespace
{

template<
	typename T
>
sge::renderer::any_matrix const
multiply_visitor::operator()(
	T const &t) const
{
	typedef typename T::value_type value_type;
	return t * sge::math::matrix::scaling<
		value_type
	>(
		static_cast<value_type>(1),
		static_cast<value_type>(-1),
		static_cast<value_type>(1));
}

}

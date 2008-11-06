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


#include <sge/renderer/vector_convert.hpp>
#include <sge/renderer/basic_any_vector.hpp>
#include <sge/math/vector.hpp>
#include <sge/export.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

namespace
{

template<
	typename Dest
>
struct visitor : boost::static_visitor<Dest> {
	template<
		typename T
	>
	Dest const operator()(
		T const &) const;
};

}

template<
	typename Dest,
	typename Source
>
Dest const
sge::renderer::vector_convert(
	Source const &v)
{
	return boost::apply_visitor(
		visitor<Dest>(),
		v);
}

namespace
{

template<
	typename Dest
>
template<
	typename T
>
Dest const
visitor<Dest>::operator()(
	T const &v) const
{
	return sge::math::structure_cast<
		typename Dest::value_type
	>(v);
}

}

#define SGE_INSTANTIATE_VECTOR_CONVERT(t, n)\
template SGE_SYMBOL \
sge::math::basic_vector<t, n> const \
sge::renderer::vector_convert(\
	sge::renderer::basic_any_vector<n>::type const &);

#define SGE_INSTANTIATE_VECTOR_CONVERT_N(n)\
SGE_INSTANTIATE_VECTOR_CONVERT(float, n)\
SGE_INSTANTIATE_VECTOR_CONVERT(double, n)

SGE_INSTANTIATE_VECTOR_CONVERT_N(3)
SGE_INSTANTIATE_VECTOR_CONVERT_N(4)

#undef SGE_INSTANTIATE_VECTOR_CONVERT_N
#undef SGE_INSTANTIATE_VECTOR_CONVERT

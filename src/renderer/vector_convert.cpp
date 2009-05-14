/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/math/vector/static.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/export.hpp>

namespace
{

template<
	typename Dest
>
class visitor {
public:
	typedef Dest result_type;

	template<
		typename T
	>
	result_type const
	operator()(
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
	return variant::apply_unary(
		visitor<Dest>(),
		v
	);
}

namespace
{

template<
	typename Dest
>
template<
	typename T
>
typename visitor<Dest>::result_type const
visitor<Dest>::operator()(
	T const &v) const
{
	return sge::math::vector::structure_cast<
		Dest
	>(v);
}

}

#define SGE_INSTANTIATE_VECTOR_CONVERT(t, n)\
template SGE_SYMBOL \
sge::math::vector::static_<t, n>::type const \
sge::renderer::vector_convert(\
	sge::renderer::basic_any_vector<n>::type const &);

#define SGE_INSTANTIATE_VECTOR_CONVERT_N(n)\
SGE_INSTANTIATE_VECTOR_CONVERT(float, n)\
SGE_INSTANTIATE_VECTOR_CONVERT(double, n)

SGE_INSTANTIATE_VECTOR_CONVERT_N(2)
SGE_INSTANTIATE_VECTOR_CONVERT_N(3)
SGE_INSTANTIATE_VECTOR_CONVERT_N(4)

#undef SGE_INSTANTIATE_VECTOR_CONVERT_N
#undef SGE_INSTANTIATE_VECTOR_CONVERT

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
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/export_symbol.hpp>

namespace
{

template<
	typename Dest
>
class visitor
{
public:
	typedef Dest result_type;

	template<
		typename T
	>
	result_type const
	operator()(
		T const &
	) const;
};

}

template<
	typename DestType,
	sge::renderer::size_type Size
>
typename fcppt::math::vector::static_<
	DestType,
	Size
>::type const
sge::renderer::vector_convert(
	typename basic_any_vector<
		Size
	>::type const &_source
)
{
	return
		fcppt::variant::apply_unary(
			visitor<
				typename fcppt::math::vector::static_<
					DestType,
					Size
				>::type
			>(),
			_source
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
	T const &_value
) const
{
	return
		fcppt::math::vector::structure_cast<
			Dest
		>(
			_value
		);
}

}

#define SGE_INSTANTIATE_VECTOR_CONVERT(\
	elemtype,\
	size\
)\
template FCPPT_EXPORT_SYMBOL \
fcppt::math::vector::static_<\
	elemtype,\
	size\
>::type const \
sge::renderer::vector_convert<\
	elemtype,\
	size\
>(\
	sge::renderer::basic_any_vector<\
		size\
	>::type const &\
);

#define SGE_INSTANTIATE_VECTOR_CONVERT_N(n)\
SGE_INSTANTIATE_VECTOR_CONVERT(float, n)\
SGE_INSTANTIATE_VECTOR_CONVERT(double, n)

SGE_INSTANTIATE_VECTOR_CONVERT_N(2)
SGE_INSTANTIATE_VECTOR_CONVERT_N(3)
SGE_INSTANTIATE_VECTOR_CONVERT_N(4)

#undef SGE_INSTANTIATE_VECTOR_CONVERT_N
#undef SGE_INSTANTIATE_VECTOR_CONVERT

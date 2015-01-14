/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_NOISE_PERLIN_OBJECT_DECL_HPP_INCLUDED
#define SGE_NOISE_PERLIN_OBJECT_DECL_HPP_INCLUDED

#include <sge/noise/perlin/object_fwd.hpp>
#include <fcppt/container/grid/object_impl.hpp>
#include <fcppt/math/vector/static_fwd.hpp>
#include <fcppt/preprocessor/pure.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace noise
{
namespace perlin
{
template
<
	typename Float,
	std::size_t N,
	typename Interpolator
>
class object
{
	static_assert(
		std::is_floating_point<
			Float
		>::value,
		"Float must be a floating-point type"
	);
public:
	typedef
	Float
	value_type;

	typedef
	fcppt::container::grid::object<value_type,N>
	grid_type;

	typedef
	fcppt::math::vector::static_
	<
		value_type,
		N
	>
	vector_type;

	typedef typename
	grid_type::dim
	dim;

	template<typename Rng>
	object(
		dim const &,
		Rng &);

	value_type
	sample(
		vector_type) const
	FCPPT_PP_PURE;
private:
	grid_type gradients_;
};
}
}
}

#endif


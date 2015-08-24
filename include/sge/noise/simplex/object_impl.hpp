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


#ifndef SGE_NOISE_SIMPLEX_OBJECT_IMPL_HPP_INCLUDED
#define SGE_NOISE_SIMPLEX_OBJECT_IMPL_HPP_INCLUDED

#include <sge/noise/simplex/object_decl.hpp>
#include <sge/noise/simplex/detail/mod.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/algorithm/array_init.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dot.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/algorithm/random_shuffle.hpp>
#include <boost/range/algorithm_ext/iota.hpp>
#include <cmath>
#include <cstddef>
#include <vector>
#include <fcppt/config/external_end.hpp>

template<
	typename Float,
	std::size_t N
>
sge::noise::simplex::object<
	Float,
	N
>::object(
		sge::noise::simplex::width const &_width)
:
	perm_(
		_width.get()),
	// TODO: Initialize this directly!
	gradients_(
		fcppt::algorithm::array_init<
			gradient_array
		>(
			fcppt::math::vector::null<
				vector_type
			>()
		)
	)
{
	boost::iota(
		perm_,
		static_cast<
			index_type
		>(
			0
		)
	);

	boost::random_shuffle(
		perm_
	);

	for (typename vector_type::size_type i = 0u; i < N; i++)
	{
		vector_type tmp(
			fcppt::math::vector::null<
				vector_type
			>()
		);
		tmp[i] = static_cast<Float>(1);
		gradients_[2u*i] = tmp;
		tmp[i] = static_cast<Float>(-1);
		gradients_[2u*i+1u] = tmp;
	}
}

template<typename Float, std::size_t N>
Float
sge::noise::simplex::object<Float,N>::sample(
	vector_type const &in)
{
	Float res = static_cast<Float>(0);
	vector_type tmp = stretch_m() * in;
	for(
		auto &elem
		:
		tmp.storage()
	)
	{
		elem = std::floor(elem);
	}
	vector_type floored(tmp);
	tmp = inv_m() * tmp;
	tmp = in - tmp;
	vector_type offset(tmp);
	tmp = stretch_m() * tmp;

	corner_array c = corners(tmp);
	for (typename corner_array::const_iterator v = c.begin(); v != c.end(); ++v)
	{
		vector_type t(in - inv_m() * (floored + *v));
		res +=
			contrib(t, floored + *v);
	}

	// FIXME: replace this magic number with something sensible
	return static_cast<Float>(40.0) * res;
}

template<typename Float, std::size_t N>
std::size_t
sge::noise::simplex::object<Float,N>::index(
	vector_type const &vec)
{
	std::size_t res = static_cast<std::size_t>(0);
	for (
		auto const elem
		:
		vec.storage()
	)
	{
		long t = static_cast<long>(elem);
		res = perm_[sge::noise::simplex::detail::mod(
			static_cast<long>(res) +
				static_cast<long>(t),
			perm_.size())];
	}
	return res;
}

template<typename Float, std::size_t N>
typename sge::noise::simplex::object<Float,N>::corner_array
sge::noise::simplex::object<Float,N>::corners(
	vector_type point)
{
	// TODO: Initialize this directly!
	corner_array res(
		fcppt::algorithm::array_init<
			corner_array
		>(
			fcppt::math::vector::null<
				vector_type
			>()
		)
	);

	vector_type cur(
		fcppt::math::vector::null<
			vector_type
		>()
	);

	Float max = static_cast<Float>(-1);
	typename vector_type::size_type max_i = 0;

	res[0] = vector_type(cur);

	for (typename vector_type::size_type j = 0; j < N; ++j)
	{
		for (typename vector_type::size_type i = 0; i < N; ++i)
			if (point[i] > max)
			{
				max = point[i];
				max_i = i;
			}
		max = static_cast<Float>(-1);
		point[max_i] = static_cast<Float>(-2);
		cur += fcppt::math::vector::unit<vector_type>(max_i);
		res[j+1] = vector_type(cur);
	}

	return res;
}

template<typename Float, std::size_t N>
Float
sge::noise::simplex::object<Float,N>::stretch_factor()
{
	return static_cast<Float>(
		1.0/(1.0 + std::sqrt(1.0 + N))
	);
}

template<typename Float, std::size_t N>
Float
sge::noise::simplex::object<Float,N>::inv_factor()
{
	return static_cast<Float>(
		-1.0/(1.0 + N + std::sqrt(1.0 + N))
	);
}

template<typename Float, std::size_t N>
typename sge::noise::simplex::object<Float,N>::matrix
sge::noise::simplex::object<Float,N>::stretch_m()
{
	matrix tmp{
		fcppt::no_init()};

	for (typename matrix::size_type i = 0; i < N; ++i)
		for (typename matrix::size_type j = 0; j < N; ++j)
			tmp[i][j] =
				stretch_factor() +
				((i == j)? 1 : 0 );
	return tmp;
}

template<typename Float, std::size_t N>
typename sge::noise::simplex::object<Float,N>::matrix
sge::noise::simplex::object<Float,N>::inv_m()
{
	matrix tmp{
		fcppt::no_init()};

	for (typename matrix::size_type i = 0; i < N; ++i)
		for (typename matrix::size_type j = 0; j < N; ++j)
			tmp[i][j] =
				inv_factor() +
				((i == j)? 1 : 0 );
	return tmp;
}

template<typename Float, std::size_t N>
Float
sge::noise::simplex::object<Float,N>::contrib(
	vector_type const &v,
	vector_type const &intv)
{
	Float t = static_cast<Float>(0.6);
	t -= fcppt::math::vector::dot(v,v);
	if (t < 0)
		return static_cast<Float>(0);
	else
		t *= t;
		return t * t * fcppt::math::vector::dot(
			gradients_[
				index(intv) % (2u * N)],
			v);
}

#endif

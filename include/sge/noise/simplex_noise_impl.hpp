/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_NOISE_SIMPLEX_NOISE_IMPL_HPP_INCLUDED
#define SGE_NOISE_SIMPLEX_NOISE_IMPL_HPP_INCLUDED

#include <sge/noise/simplex_noise_decl.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dot.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/algorithm/random_shuffle.hpp>
#include <boost/range/algorithm_ext/iota.hpp>
#include <cmath>
#include <cstddef>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{
	std::size_t
	mod(
		long const &a,
		std::size_t const &b)
	{
		if (a >= 0)
			return static_cast<std::size_t>(a) %
				static_cast<std::size_t>(b);
		else
			return static_cast<std::size_t>(-a) %
				static_cast<std::size_t>(b);
	}
}

template<
	typename Float,
	std::size_t N
>
sge::noise::simplex_noise<
	Float,
	N>::simplex_noise(
		std::size_t const _dim,
		std::size_t const _width)
:
	dim_(
		_dim),
	perm_(
		_width)
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

	for (typename vector::size_type i = 0; i < N; ++i)
	{
		vector tmp = vector::null();
		tmp[i] = static_cast<Float>(1);
		gradients_.push_back(tmp);
		tmp[i] = static_cast<Float>(-1);
		gradients_.push_back(tmp);
	}
}

template<typename Float, std::size_t N>
Float
sge::noise::simplex_noise<Float,N>::sample(
	vector const &in)
{
	Float res = static_cast<Float>(0);
	vector tmp = stretch_m() * in;
	for(typename vector::iterator it = tmp.begin(); it != tmp.end(); ++it)
	{
		*it = std::floor(*it);
	}
	vector floored(tmp);
	tmp = inv_m() * tmp;
	tmp = in - tmp;
	vector offset(tmp);
	tmp = stretch_m() * tmp;

	corner_array c = corners(tmp);
	for (typename corner_array::const_iterator v = c.begin(); v != c.end(); ++v)
	{
		vector t(in - inv_m() * (floored + *v));
		res +=
			contrib(t, floored + *v);
	}

	// FIXME: replace this magic number with something sensible
	return static_cast<Float>(40.0) * res;
}

template<typename Float, std::size_t N>
std::size_t
sge::noise::simplex_noise<Float,N>::index(
	vector const &vec)
{
	std::size_t res = static_cast<std::size_t>(0);
	for (typename vector::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		long t = static_cast<long>(*it);
		res = perm_[::mod(
			static_cast<long>(res) +
				static_cast<long>(t),
			perm_.size())];
	}
	return res;
}

template<typename Float, std::size_t N>
typename sge::noise::simplex_noise<Float,N>::corner_array
sge::noise::simplex_noise<Float,N>::corners(
	vector point)
{
	corner_array res;
	vector cur = vector::null();
	Float max = static_cast<Float>(-1);
	typename vector::size_type max_i = 0;

	res[0] = vector(cur);

	for (typename vector::size_type j = 0; j < N; ++j)
	{
		for (typename vector::size_type i = 0; i < N; ++i)
			if (point[i] > max)
			{
				max = point[i];
				max_i = i;
			}
		max = static_cast<Float>(-1);
		point[max_i] = static_cast<Float>(-2);
		cur += fcppt::math::vector::unit<vector>(max_i);
		res[j+1] = vector(cur);
	}

	return res;
}

template<typename Float, std::size_t N>
Float
sge::noise::simplex_noise<Float,N>::stretch_factor()
{
	return static_cast<Float>(
		1.0/(1.0 + std::sqrt(1.0 + N))
	);
}

template<typename Float, std::size_t N>
Float
sge::noise::simplex_noise<Float,N>::inv_factor()
{
	return static_cast<Float>(
		-1.0/(1.0 + N + std::sqrt(1.0 + N))
	);
}

template<typename Float, std::size_t N>
typename sge::noise::simplex_noise<Float,N>::matrix
sge::noise::simplex_noise<Float,N>::stretch_m()
{
	matrix tmp;
	for (typename matrix::size_type i = 0; i < N; ++i)
		for (typename matrix::size_type j = 0; j < N; ++j)
			tmp[i][j] =
				stretch_factor() +
				((i == j)? 1 : 0 );
	return tmp;
}

template<typename Float, std::size_t N>
typename sge::noise::simplex_noise<Float,N>::matrix
sge::noise::simplex_noise<Float,N>::inv_m()
{
	matrix tmp;
	for (typename matrix::size_type i = 0; i < N; ++i)
		for (typename matrix::size_type j = 0; j < N; ++j)
			tmp[i][j] =
				inv_factor() +
				((i == j)? 1 : 0 );
	return tmp;
}

template<typename Float, std::size_t N>
Float
sge::noise::simplex_noise<Float,N>::contrib(
	vector const &v,
	vector const &intv)
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

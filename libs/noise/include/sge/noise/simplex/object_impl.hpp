//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_NOISE_SIMPLEX_OBJECT_IMPL_HPP_INCLUDED
#define SGE_NOISE_SIMPLEX_OBJECT_IMPL_HPP_INCLUDED

#include <sge/noise/simplex/object_decl.hpp>
#include <sge/noise/simplex/detail/mod.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/container/array/init_const.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/to_array.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dot.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/unit.hpp>
#include <fcppt/random/generator/mt19937.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>
#include <fcppt/config/external_end.hpp>


template<
	typename Float,
	fcppt::math::size_type N
>
sge::noise::simplex::object<
	Float,
	N
>::object(
	sge::noise::simplex::width const &_width
)
:
	perm_(
		_width.get()),
	// TODO(philipp): Initialize this directly!
	gradients_(
		fcppt::container::array::init_const<
			gradient_array
		>(
			fcppt::math::vector::null<
				vector_type
			>()
		)
	)
{
	std::iota(
		perm_.begin(),
		perm_.end(),
		static_cast<
			index_type
		>(
			0
		)
	);

	{
		using
		generator_type
		=
		fcppt::random::generator::mt19937;

		generator_type randgen{
			fcppt::random::generator::seed_from_chrono<
				generator_type::seed
			>()
		};

		std::shuffle(
			perm_.begin(),
			perm_.end(),
			randgen
		);
	}

	for (typename vector_type::size_type i = 0U; i < N; i++)
	{
		vector_type tmp(
			fcppt::math::vector::null<
				vector_type
			>()
		);
		tmp.get_unsafe(i) = static_cast<Float>(1);
		gradients_[2U*i] = tmp;
		tmp.get_unsafe(i) = static_cast<Float>(-1);
		gradients_[2U*i+1U] = tmp;
	}
}

template<
	typename Float,
	fcppt::math::size_type N
>
Float
sge::noise::simplex::object<Float,N>::sample(
	vector_type const &in)
{
	auto res = static_cast<Float>(0);
	vector_type tmp = stretch_m() * in;
	for(
		auto &elem
		:
		fcppt::math::to_array(
			tmp
		)
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
	for (auto const &v : c)
	{
		vector_type t(in - inv_m() * (floored + v));
		res +=
			contrib(t, floored + v);
	}

	// FIXME: replace this magic number with something sensible
	return static_cast<Float>(40.0) * res;
}

template<
	typename Float,
	fcppt::math::size_type N
>
std::size_t
sge::noise::simplex::object<Float,N>::index(
	vector_type const &vec)
{
	auto res = static_cast<std::size_t>(0);
	for (
		auto const elem
		:
		fcppt::math::to_array(
			vec
		)
	)
	{
		auto t = static_cast<long>(elem); // NOLINT(google-runtime-int)
		res = perm_[sge::noise::simplex::detail::mod(
			static_cast<long>(res) + // NOLINT(google-runtime-int)
				static_cast<long>(t), // NOLINT(google-runtime-int)
			perm_.size())];
	}
	return res;
}

template<
	typename Float,
	fcppt::math::size_type N
>
typename sge::noise::simplex::object<Float,N>::corner_array
sge::noise::simplex::object<Float,N>::corners(
	vector_type point)
{
	// TODO(philipp): Initialize this directly!
	auto res(
		fcppt::container::array::init_const<
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

	auto max = static_cast<Float>(-1);
	typename vector_type::size_type max_i = 0;

	res[0] = vector_type(cur);

	for (typename vector_type::size_type j = 0; j < N; ++j)
	{
		for (typename vector_type::size_type i = 0; i < N; ++i)
		{
			if (point.get_unsafe(i) > max)
			{
				max = point.get_unsafe(i);
				max_i = i;
			}
		}
		max = static_cast<Float>(-1);
		point.get_unsafe(max_i) = static_cast<Float>(-2);
		cur += fcppt::math::vector::unit<vector_type>(max_i);
		res[j+1] = vector_type(cur); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
	}

	return res;
}

template<
	typename Float,
	fcppt::math::size_type N
>
Float
sge::noise::simplex::object<Float,N>::stretch_factor()
{
	return static_cast<Float>(
		1.0/(1.0 + std::sqrt(1.0 + N))
	);
}

template<
	typename Float,
	fcppt::math::size_type N
>
Float
sge::noise::simplex::object<Float,N>::inv_factor()
{
	return static_cast<Float>(
		-1.0/(1.0 + N + std::sqrt(1.0 + N))
	);
}

template<
	typename Float,
	fcppt::math::size_type N
>
typename sge::noise::simplex::object<Float,N>::matrix
sge::noise::simplex::object<Float,N>::stretch_m()
{
	matrix tmp{
		fcppt::no_init()};

	for (typename matrix::size_type i = 0; i < N; ++i)
	{
		for (typename matrix::size_type j = 0; j < N; ++j)
		{
			tmp.get_unsafe(i).get_unsafe(j) =
				stretch_factor() +
				((i == j)? 1 : 0 );
		}
	}
	return tmp;
}

template<
	typename Float,
	fcppt::math::size_type N
>
typename sge::noise::simplex::object<Float,N>::matrix
sge::noise::simplex::object<Float,N>::inv_m()
{
	matrix tmp{
		fcppt::no_init()};

	for (typename matrix::size_type i = 0; i < N; ++i)
	{
		for (typename matrix::size_type j = 0; j < N; ++j)
		{
			tmp.get_unsafe(i).get_unsafe(j) =
				inv_factor() +
				((i == j)? 1 : 0 );
		}
	}
	return tmp;
}

template<
	typename Float,
	fcppt::math::size_type N
>
Float
sge::noise::simplex::object<Float,N>::contrib(
	vector_type const &v,
	vector_type const &intv)
{
	auto t = static_cast<Float>(0.6); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

	t -= fcppt::math::vector::dot(v,v);

	if (t < 0)
	{
		return static_cast<Float>(0);
	}

	t *= t;

	return
		t * t * fcppt::math::vector::dot(
			gradients_[
				index(intv) % (2U * N)],
			v
		);
}

#endif

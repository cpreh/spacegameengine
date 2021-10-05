//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_BRESENHAM_THICK_HPP_INCLUDED
#define SGE_BRESENHAM_THICK_HPP_INCLUDED

#include <sge/bresenham/detail/impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::bresenham
{

/**
\brief Thick version of the bresenham algorithm

Plots points using bresenham between \a _start and \a _end. For each point in
the set, \a _callback is called. If \a _callback returns <code>false</code>
the algorithm stops.

\tparam Callback A function callable as <code>bool (fcppt::math::vector::static_<T,2>)</code>

\return <code>true</code> iff every call to \a _callback returns <code>true</code>
*/
template<
	typename T,
	typename S1,
	typename S2,
	typename Callback
>
inline
bool
thick(
	fcppt::math::vector::object<
		T,
		2,
		S1
	> const _start,
	fcppt::math::vector::object<
		T,
		2,
		S2
	> const _end,
	Callback const &_callback
)
{
	return
		sge::bresenham::detail::impl<
			true
		>(
			_start,
			_end,
			_callback
		);
}

}

#endif

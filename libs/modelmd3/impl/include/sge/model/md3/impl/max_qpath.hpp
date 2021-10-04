//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_MAX_QPATH_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_MAX_QPATH_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::model::md3::impl
{

using
max_qpath
=
std::integral_constant<
	unsigned,
	64U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
>;

}

#endif

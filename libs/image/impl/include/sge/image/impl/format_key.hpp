//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_FORMAT_KEY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_FORMAT_KEY_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::image::impl
{

template<
	typename Dynamic,
	Dynamic DynamicValue
>
using
format_key
=
std::integral_constant<
	Dynamic,
	DynamicValue
>;

}

#endif

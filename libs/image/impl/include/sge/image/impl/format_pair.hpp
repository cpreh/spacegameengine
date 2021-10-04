//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_FORMAT_PAIR_HPP_INCLUDED
#define SGE_IMAGE_IMPL_FORMAT_PAIR_HPP_INCLUDED

#include <sge/image/impl/format_key.hpp>
#include <fcppt/mpl/map/element.hpp>


namespace sge::image::impl
{

template<
	typename Dynamic,
	Dynamic DynamicValue,
	typename Static
>
using
format_pair
=
fcppt::mpl::map::element<
	sge::image::impl::format_key<
		Dynamic,
		DynamicValue
	>,
	Static
>;

}

#endif

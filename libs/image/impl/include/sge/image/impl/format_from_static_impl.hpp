//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_FORMAT_FROM_STATIC_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_FORMAT_FROM_STATIC_IMPL_HPP_INCLUDED

#include <sge/image/enable_if_has_format.hpp>
#include <sge/image/format_from_static.hpp>
#include <sge/image/impl/static_to_dynamic_format.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>


template<
	typename Tag,
	typename Format
>
sge::image::enable_if_has_format<
	Tag,
	Format,
	sge::image::traits::pixel::format<
		Tag
	>
>
sge::image::format_from_static()
{
	return
		sge::image::impl::static_to_dynamic_format<
			Tag,
			Format
		>::value;
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_INSTANTIATE_FORMAT_FROM_STATIC_HPP_INCLUDED
#define SGE_IMAGE_IMPL_INSTANTIATE_FORMAT_FROM_STATIC_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/enable_if_has_format.hpp>
#include <sge/image/impl/format_from_static_impl.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>


#define SGE_IMAGE_IMPL_INSTANTIATE_FORMAT_FROM_STATIC(\
	tag,\
	format_arg\
)\
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
sge::image::enable_if_has_format<\
	tag,\
	format_arg,\
	sge::image::traits::pixel::format< \
		tag \
	> \
> \
sge::image::format_from_static<\
	tag,\
	format_arg\
>()

#endif

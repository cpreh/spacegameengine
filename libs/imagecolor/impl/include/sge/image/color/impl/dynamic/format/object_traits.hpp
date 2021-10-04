//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_OBJECT_TRAITS_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_OBJECT_TRAITS_HPP_INCLUDED

#include <sge/image/color/impl/dynamic/format/object_fwd.hpp>
#include <mizuiro/size_type.hpp>
#include <mizuiro/color/format/tag_of_fwd.hpp>
#include <mizuiro/color/format/homogenous_dynamic_ns/tag.hpp>


namespace mizuiro::color::format
{

template<
	typename Space,
	typename BaseType,
	mizuiro::size_type NumChannels
>
struct tag_of<
	sge::image::color::impl::dynamic::format::object<
		Space,
		BaseType,
		NumChannels
	>
>
{
	using
	type
	=
	mizuiro::color::format::homogenous_dynamic_ns::tag<
		sge::image::color::impl::dynamic::format::object<
			Space,
			BaseType,
			NumChannels
		>
	>;
};

}

#endif

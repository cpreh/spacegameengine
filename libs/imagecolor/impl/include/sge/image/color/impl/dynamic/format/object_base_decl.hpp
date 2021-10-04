//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_OBJECT_BASE_DECL_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_OBJECT_BASE_DECL_HPP_INCLUDED

#include <mizuiro/size_type.hpp>
#include <mizuiro/color/format/homogenous_dynamic_decl.hpp>
#include <mizuiro/color/format/include/homogenous_dynamic.hpp>


namespace sge::image::color::impl::dynamic::format
{

template<
	typename Space,
	typename BaseType,
	mizuiro::size_type NumChannels
>
using object_base
=
mizuiro::color::format::homogenous_dynamic<
	BaseType,
	Space,
	NumChannels
>;

}

#endif

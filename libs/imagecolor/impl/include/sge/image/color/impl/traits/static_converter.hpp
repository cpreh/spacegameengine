//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_TRAITS_STATIC_CONVERTER_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_TRAITS_STATIC_CONVERTER_HPP_INCLUDED

#include <sge/image/color/tag.hpp>
#include <sge/image/color/impl/converter.hpp>
#include <sge/image/impl/traits/static_converter_tpl_fwd.hpp>


namespace sge::image::impl::traits
{

template<>
struct static_converter_tpl<
	sge::image::color::tag
>
{
	using
	type
	=
	sge::image::color::impl::converter;
};

}

#endif

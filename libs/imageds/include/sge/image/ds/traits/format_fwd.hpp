//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_TRAITS_FORMAT_FWD_HPP_INCLUDED
#define SGE_IMAGE_DS_TRAITS_FORMAT_FWD_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>
#include <sge/image/ds/tag.hpp>
#include <sge/image/traits/pixel/format_tpl_fwd.hpp>


namespace sge::image::traits::pixel
{

template<>
struct format_tpl<
	sge::image::ds::tag
>
{
	using
	type
	=
	sge::image::ds::format;
};

}

#endif

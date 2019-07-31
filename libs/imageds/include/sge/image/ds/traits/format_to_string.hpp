//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_TRAITS_FORMAT_TO_STRING_HPP_INCLUDED
#define SGE_IMAGE_DS_TRAITS_FORMAT_TO_STRING_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>
#include <sge/image/ds/tag.hpp>
#include <sge/image/ds/detail/symbol.hpp>
#include <sge/image/traits/pixel/format_to_string_tpl_fwd.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace image
{
namespace traits
{
namespace pixel
{

template<>
struct format_to_string_tpl<
	sge::image::ds::tag
>
{
	SGE_IMAGE_DS_DETAIL_SYMBOL
	static
	fcppt::string
	execute(
		sge::image::ds::format
	);
};

}
}
}
}

#endif

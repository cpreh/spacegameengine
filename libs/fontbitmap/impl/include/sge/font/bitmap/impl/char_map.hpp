//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_BITMAP_IMPL_CHAR_MAP_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_CHAR_MAP_HPP_INCLUDED

#include <sge/font/char_type.hpp>
#include <sge/font/bitmap/impl/char_metric.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{
namespace impl
{

using
char_map
=
std::unordered_map<
	sge::font::char_type,
	sge::font::bitmap::impl::char_metric
>;

}
}
}
}

#endif

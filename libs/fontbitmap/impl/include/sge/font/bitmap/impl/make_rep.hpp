//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_BITMAP_IMPL_MAKE_REP_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_MAKE_REP_HPP_INCLUDED

#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/bitmap/impl/char_map.hpp>
#include <sge/font/bitmap/impl/line_height.hpp>
#include <sge/font/bitmap/impl/rep.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{
namespace impl
{

sge::font::bitmap::impl::rep
make_rep(
	fcppt::log::object &,
	sge::font::bitmap::impl::char_map const &,
	sge::font::bitmap::impl::line_height,
	sge::font::string const &,
	sge::font::text_parameters const &
);

}
}
}
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_BITMAP_CREATE_HPP_INCLUDED
#define SGE_FONT_BITMAP_CREATE_HPP_INCLUDED

#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/bitmap/detail/symbol.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{

SGE_FONT_BITMAP_DETAIL_SYMBOL
sge::font::object_unique_ptr
create(
	fcppt::log::context &,
	std::filesystem::path const &,
	sge::image2d::system &
);

}
}
}

#endif

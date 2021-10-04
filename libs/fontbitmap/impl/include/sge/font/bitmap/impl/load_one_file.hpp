//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_BITMAP_IMPL_LOAD_ONE_FILE_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_LOAD_ONE_FILE_HPP_INCLUDED

#include <sge/font/bitmap/impl/char_map.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge::font::bitmap::impl
{

std::pair<
	sge::image2d::file_unique_ptr,
	sge::font::bitmap::impl::char_map
>
load_one_file(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	std::filesystem::path const &stem,
	sge::parse::json::object const &,
	sge::image2d::system_ref
);

}

#endif

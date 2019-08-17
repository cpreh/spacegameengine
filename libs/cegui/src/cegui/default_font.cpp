//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/default_font.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sge::cegui::default_font::default_font(
	std::filesystem::path const &_path,
	float const _font_size
)
:
	path_(_path),
	font_size_(_font_size)
{
}

std::filesystem::path const &
sge::cegui::default_font::path() const
{
	return path_;
}

float
sge::cegui::default_font::font_size() const
{
	return font_size_;
}

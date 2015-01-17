/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_CEGUI_LOAD_CONTEXT_HPP_INCLUDED
#define SGE_CEGUI_LOAD_CONTEXT_HPP_INCLUDED

#include <sge/cegui/default_font.hpp>
#include <sge/cegui/load_context_fwd.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cegui
{

class load_context
{
public:
	SGE_CEGUI_DETAIL_SYMBOL
	explicit
	load_context(
		boost::filesystem::path const &scheme_file
	);

	boost::filesystem::path const &
	scheme_file() const;

	SGE_CEGUI_DETAIL_SYMBOL
	sge::cegui::load_context &
	font_directory(
		boost::filesystem::path const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	sge::cegui::load_context &
	looknfeel_directory(
		boost::filesystem::path const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	sge::cegui::load_context &
	imageset_directory(
		boost::filesystem::path const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	sge::cegui::load_context &
	default_font(
		sge::cegui::default_font const &
	);

	typedef fcppt::optional<
		boost::filesystem::path
	> optional_path;

	typedef fcppt::optional<
		sge::cegui::default_font
	> optional_default_font;

	sge::cegui::load_context::optional_path const &
	font_directory() const;

	sge::cegui::load_context::optional_path const &
	looknfeel_directory() const;

	sge::cegui::load_context::optional_path const &
	imageset_directory() const;

	sge::cegui::load_context::optional_default_font const &
	default_font() const;
private:
	boost::filesystem::path scheme_file_;

	sge::cegui::load_context::optional_path font_directory_;

	sge::cegui::load_context::optional_path looknfeel_directory_;

	sge::cegui::load_context::optional_path imageset_directory_;

	sge::cegui::load_context::optional_default_font default_font_;
};

}
}

#endif

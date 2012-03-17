/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/cegui/symbol.hpp>
#include <fcppt/optional.hpp>
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
	SGE_CEGUI_SYMBOL explicit
	load_context(
		boost::filesystem::path const &scheme_file);

	boost::filesystem::path const &
	scheme_file() const;

	SGE_CEGUI_SYMBOL load_context &
	font_directory(
		boost::filesystem::path const &);

	SGE_CEGUI_SYMBOL load_context &
	looknfeel_directory(
		boost::filesystem::path const &);

	SGE_CEGUI_SYMBOL load_context &
	imageset_directory(
		boost::filesystem::path const &);

	SGE_CEGUI_SYMBOL load_context &
	default_font(
		cegui::default_font const &);

	fcppt::optional<boost::filesystem::path> const &
	font_directory() const;

	fcppt::optional<boost::filesystem::path> const &
	looknfeel_directory() const;

	fcppt::optional<boost::filesystem::path> const &
	imageset_directory() const;

	fcppt::optional<cegui::default_font> const &
	default_font() const;
private:
	boost::filesystem::path scheme_file_;
	fcppt::optional<boost::filesystem::path> font_directory_;
	fcppt::optional<boost::filesystem::path> looknfeel_directory_;
	fcppt::optional<boost::filesystem::path> imageset_directory_;
	fcppt::optional<cegui::default_font> default_font_;
};
}
}

#endif

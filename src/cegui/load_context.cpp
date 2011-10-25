/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cegui/default_font.hpp>
#include <sge/cegui/load_context.hpp>
#include <fcppt/filesystem/path.hpp>


sge::cegui::load_context::load_context(
	fcppt::filesystem::path const &_scheme_file)
:
	scheme_file_(
		_scheme_file),
	font_directory_(),
	looknfeel_directory_(),
	imageset_directory_(),
	default_font_()
{
}

fcppt::filesystem::path const &
sge::cegui::load_context::scheme_file() const
{
	return scheme_file_;
}

sge::cegui::load_context &
sge::cegui::load_context::font_directory(
	fcppt::filesystem::path const &_font_directory)
{
	font_directory_ = _font_directory;
	return *this;
}

sge::cegui::load_context &
sge::cegui::load_context::looknfeel_directory(
	fcppt::filesystem::path const &_looknfeel_directory)
{
	looknfeel_directory_ = _looknfeel_directory;
	return *this;
}

sge::cegui::load_context &
sge::cegui::load_context::imageset_directory(
	fcppt::filesystem::path const &_imageset_directory)
{
	imageset_directory_ = _imageset_directory;
	return *this;
}

sge::cegui::load_context &
sge::cegui::load_context::default_font(
	cegui::default_font const &_default_font)
{
	default_font_ = _default_font;
	return *this;
}

fcppt::optional<fcppt::filesystem::path> const &
sge::cegui::load_context::font_directory() const
{
	return font_directory_;
}

fcppt::optional<fcppt::filesystem::path> const &
sge::cegui::load_context::looknfeel_directory() const
{
	return looknfeel_directory_;
}

fcppt::optional<fcppt::filesystem::path> const &
sge::cegui::load_context::imageset_directory() const
{
	return imageset_directory_;
}

fcppt::optional<sge::cegui::default_font> const &
sge::cegui::load_context::default_font() const
{
	return default_font_;
}

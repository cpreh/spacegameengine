//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/default_font.hpp>
#include <sge/cegui/load_context.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::cegui::load_context::load_context(
	boost::filesystem::path const &_scheme_file
)
:
	scheme_file_{
		_scheme_file
	},
	font_directory_(),
	looknfeel_directory_(),
	imageset_directory_(),
	default_font_()
{
}

boost::filesystem::path const &
sge::cegui::load_context::scheme_file() const
{
	return
		scheme_file_;
}

sge::cegui::load_context &
sge::cegui::load_context::font_directory(
	boost::filesystem::path const &_font_directory
)
{
	font_directory_ =
		optional_path{
			_font_directory
		};

	return
		*this;
}

sge::cegui::load_context &
sge::cegui::load_context::looknfeel_directory(
	boost::filesystem::path const &_looknfeel_directory
)
{
	looknfeel_directory_ =
		optional_path{
			_looknfeel_directory
		};

	return
		*this;
}

sge::cegui::load_context &
sge::cegui::load_context::imageset_directory(
	boost::filesystem::path const &_imageset_directory
)
{
	imageset_directory_ =
		optional_path{
			_imageset_directory
		};

	return
		*this;
}

sge::cegui::load_context &
sge::cegui::load_context::default_font(
	sge::cegui::default_font const &_default_font
)
{
	default_font_ =
		optional_default_font{
			_default_font
		};

	return
		*this;
}

sge::cegui::load_context::optional_path const &
sge::cegui::load_context::font_directory() const
{
	return
		font_directory_;
}

sge::cegui::load_context::optional_path const &
sge::cegui::load_context::looknfeel_directory() const
{
	return
		looknfeel_directory_;
}

sge::cegui::load_context::optional_path const &
sge::cegui::load_context::imageset_directory() const
{
	return
		imageset_directory_;
}

sge::cegui::load_context::optional_default_font const &
sge::cegui::load_context::default_font() const
{
	return
		default_font_;
}

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/default_font.hpp>
#include <sge/cegui/load_context.hpp>
#include <sge/cegui/scheme_file.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::cegui::load_context::load_context(sge::cegui::scheme_file &&_scheme_file)
    : scheme_file_{std::move(_scheme_file)},
      font_directory_(),
      looknfeel_directory_(),
      imageset_directory_(),
      default_font_()
{
}

std::filesystem::path const &sge::cegui::load_context::scheme_file() const
{
  return scheme_file_.get();
}

sge::cegui::load_context &
sge::cegui::load_context::font_directory(std::filesystem::path &&_font_directory)
{
  font_directory_ = optional_path{std::move(_font_directory)};

  return *this;
}

sge::cegui::load_context &
sge::cegui::load_context::looknfeel_directory(std::filesystem::path &&_looknfeel_directory)
{
  looknfeel_directory_ = optional_path{std::move(_looknfeel_directory)};

  return *this;
}

sge::cegui::load_context &
sge::cegui::load_context::imageset_directory(std::filesystem::path &&_imageset_directory)
{
  imageset_directory_ = optional_path{std::move(_imageset_directory)};

  return *this;
}

sge::cegui::load_context &
sge::cegui::load_context::default_font(sge::cegui::default_font &&_default_font)
{
  default_font_ = optional_default_font{std::move(_default_font)};

  return *this;
}

sge::cegui::load_context::optional_path const &sge::cegui::load_context::font_directory() const
{
  return font_directory_;
}

sge::cegui::load_context::optional_path const &sge::cegui::load_context::looknfeel_directory() const
{
  return looknfeel_directory_;
}

sge::cegui::load_context::optional_path const &sge::cegui::load_context::imageset_directory() const
{
  return imageset_directory_;
}

sge::cegui::load_context::optional_default_font const &
sge::cegui::load_context::default_font() const
{
  return default_font_;
}

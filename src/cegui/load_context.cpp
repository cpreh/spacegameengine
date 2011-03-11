#include <sge/cegui/load_context.hpp>

sge::cegui::load_context::load_context(
	fcppt::filesystem::path const &_scheme_file)
:
	scheme_file_(
		_scheme_file),
	font_directory_(),
	looknfeel_directory_()
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

#ifndef SGE_CEGUI_LOAD_CONTEXT_HPP_INCLUDED
#define SGE_CEGUI_LOAD_CONTEXT_HPP_INCLUDED

#include <sge/cegui/symbol.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/optional.hpp>

namespace sge
{
namespace cegui
{
class load_context
{
public:
	SGE_CEGUI_SYMBOL explicit
	load_context(
		fcppt::filesystem::path const &scheme_file);

	fcppt::filesystem::path const &
	scheme_file() const;

	SGE_CEGUI_SYMBOL load_context &
	font_directory(
		fcppt::filesystem::path const &);

	SGE_CEGUI_SYMBOL load_context &
	looknfeel_directory(
		fcppt::filesystem::path const &);

	SGE_CEGUI_SYMBOL load_context &
	imageset_directory(
		fcppt::filesystem::path const &);

	fcppt::optional<fcppt::filesystem::path> const &
	font_directory() const;

	fcppt::optional<fcppt::filesystem::path> const &
	looknfeel_directory() const;

	fcppt::optional<fcppt::filesystem::path> const &
	imageset_directory() const;
private:
	fcppt::filesystem::path scheme_file_;
	fcppt::optional<fcppt::filesystem::path> font_directory_;
	fcppt::optional<fcppt::filesystem::path> looknfeel_directory_;
	fcppt::optional<fcppt::filesystem::path> imageset_directory_;
};
}
}

#endif

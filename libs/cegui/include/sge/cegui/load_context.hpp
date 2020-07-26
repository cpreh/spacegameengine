//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_LOAD_CONTEXT_HPP_INCLUDED
#define SGE_CEGUI_LOAD_CONTEXT_HPP_INCLUDED

#include <sge/cegui/default_font.hpp>
#include <sge/cegui/load_context_fwd.hpp>
#include <sge/cegui/scheme_file.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
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
		sge::cegui::scheme_file &&
	);

	[[nodiscard]]
	std::filesystem::path const &
	scheme_file() const;

	SGE_CEGUI_DETAIL_SYMBOL
	sge::cegui::load_context &
	font_directory(
		std::filesystem::path &&
	);

	SGE_CEGUI_DETAIL_SYMBOL
	sge::cegui::load_context &
	looknfeel_directory(
		std::filesystem::path &&
	);

	SGE_CEGUI_DETAIL_SYMBOL
	sge::cegui::load_context &
	imageset_directory(
		std::filesystem::path &&
	);

	SGE_CEGUI_DETAIL_SYMBOL
	sge::cegui::load_context &
	default_font(
		sge::cegui::default_font &&
	);

	using
	optional_path
	=
	fcppt::optional::object<
		std::filesystem::path
	>;

	using
	optional_default_font
	=
	fcppt::optional::object<
		sge::cegui::default_font
	>;

	[[nodiscard]]
	sge::cegui::load_context::optional_path const &
	font_directory() const;

	[[nodiscard]]
	sge::cegui::load_context::optional_path const &
	looknfeel_directory() const;

	[[nodiscard]]
	sge::cegui::load_context::optional_path const &
	imageset_directory() const;

	[[nodiscard]]
	sge::cegui::load_context::optional_default_font const &
	default_font() const;
private:
	sge::cegui::scheme_file scheme_file_;

	sge::cegui::load_context::optional_path font_directory_;

	sge::cegui::load_context::optional_path looknfeel_directory_;

	sge::cegui::load_context::optional_path imageset_directory_;

	sge::cegui::load_context::optional_default_font default_font_;
};

}
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_LOAD_CONTEXT_HPP_INCLUDED
#define SGE_CEGUI_LOAD_CONTEXT_HPP_INCLUDED

#include <sge/cegui/default_font.hpp>
#include <sge/cegui/load_context_fwd.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <fcppt/optional/object_impl.hpp>
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

	typedef fcppt::optional::object<
		boost::filesystem::path
	> optional_path;

	typedef fcppt::optional::object<
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

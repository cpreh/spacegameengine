//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_TOOLBOX_SCOPED_LAYOUT_HPP_INCLUDED
#define SGE_CEGUI_TOOLBOX_SCOPED_LAYOUT_HPP_INCLUDED

#include <sge/cegui/system_ref.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class Window;
}

namespace sge::cegui::toolbox
{

class scoped_layout
{
	FCPPT_NONMOVABLE(
		scoped_layout
	);
public:
	SGE_CEGUI_DETAIL_SYMBOL
	scoped_layout(
		sge::cegui::system_ref,
		std::filesystem::path const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	~scoped_layout();

	[[nodiscard]]
	SGE_CEGUI_DETAIL_SYMBOL
	CEGUI::Window &
	window() const;
private:
	sge::cegui::system_ref const system_;

	CEGUI::Window *const window_;
};

}

#endif

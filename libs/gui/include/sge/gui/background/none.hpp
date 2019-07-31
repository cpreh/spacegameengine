//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_BACKGROUND_NONE_HPP_INCLUDED
#define SGE_GUI_BACKGROUND_NONE_HPP_INCLUDED

#include <sge/gui/background/base.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/base_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace background
{

class none
:
	public sge::gui::background::base
{
	FCPPT_NONCOPYABLE(
		none
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	explicit
	none(
		sge::gui::main_area::base &
	);

	SGE_GUI_DETAIL_SYMBOL
	~none()
	override;
private:
	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	)
	override;
};

}
}
}

#endif

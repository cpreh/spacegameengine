//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_DUMMY_HPP_INCLUDED
#define SGE_GUI_WIDGET_DUMMY_HPP_INCLUDED

#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/dummy_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class dummy
:
	public sge::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		dummy
	);
public:
	dummy();

	~dummy()
	override;
private:
	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &
	)
	override;
};

}
}
}

#endif

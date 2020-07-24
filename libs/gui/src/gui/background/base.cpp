//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/background/base.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/main_area/reference.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/widget/base.hpp>


sge::gui::background::base::base(
	sge::gui::main_area::reference const _main_area
)
:
	main_area_(
		_main_area
	)
{
}

sge::gui::background::base::~base()
= default;

void
sge::gui::background::base::draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	this->on_draw(
		_renderer,
		_context,
		this->widget().layout().area()
	);
}

sge::gui::widget::base &
sge::gui::background::base::widget()
{
	return
		main_area_.get().widget();
}

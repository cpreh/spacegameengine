//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/context_fwd.hpp>
#include <sge/gui/gravity.hpp>
#include <sge/gui/impl/gravity_east.hpp>
#include <sge/gui/impl/gravity_south.hpp>
#include <sge/gui/impl/make_container_pair.hpp>
#include <sge/gui/impl/swap_pair.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/main_area/screen_corner.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/viewport/manager_fwd.hpp>


sge::gui::main_area::screen_corner::screen_corner(
	sge::renderer::device::core &_renderer,
	sge::viewport::manager &_viewport_manager,
	sge::gui::context &_gui_context,
	sge::gui::widget::base &_widget,
	sge::gui::gravity const _gravity
)
:
	sge::gui::main_area::base(),
	widget_(
		_widget
	),
	minimum_size_(
		_widget
	),
	horizontal_expander_(
		sge::rucksack::axis::x
	),
	vertical_expander_(
		sge::rucksack::axis::y
	),
	horizontal_container_(
		_gui_context,
		sge::gui::impl::make_container_pair(
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference(
					minimum_size_
				),
				sge::rucksack::alignment::center
			},
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference(
					horizontal_expander_
				),
				sge::rucksack::alignment::center
			},
			sge::gui::impl::swap_pair{
				sge::gui::impl::gravity_east(
					_gravity
				)
			}
		),
		sge::rucksack::axis::x
	),
	vertical_container_(
		_gui_context,
		sge::gui::impl::make_container_pair(
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference(
					horizontal_container_
				),
				sge::rucksack::alignment::center
			},
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference(
					vertical_expander_
				),
				sge::rucksack::alignment::center
			},
			sge::gui::impl::swap_pair{
				sge::gui::impl::gravity_south(
					_gravity
				)
			}
		),
		sge::rucksack::axis::y
	),
	viewport_adaptor_(
		_renderer,
		_viewport_manager,
		vertical_container_
	)
{
}

sge::gui::main_area::screen_corner::~screen_corner()
{
}

void
sge::gui::main_area::screen_corner::relayout()
{
	viewport_adaptor_.relayout();
}

sge::gui::widget::base &
sge::gui::main_area::screen_corner::widget()
{
	return
		widget_;
}

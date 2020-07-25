//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_CONTAINER_HPP_INCLUDED
#define SGE_GUI_WIDGET_CONTAINER_HPP_INCLUDED

#include <sge/gui/context_ref.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/get_focus_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/container_fwd.hpp>
#include <sge/gui/widget/optional_focus_ref.hpp>
#include <sge/gui/widget/optional_ref_fwd.hpp>
#include <sge/gui/widget/reference_fwd.hpp>
#include <sge/gui/widget/reference_vector.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class container
:
	public sge::gui::widget::base
{
	FCPPT_NONMOVABLE(
		container
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	container(
		sge::gui::context_ref,
		sge::gui::widget::reference_vector &&,
		sge::rucksack::widget::reference
	);

	SGE_GUI_DETAIL_SYMBOL
	~container()
	override;

	SGE_GUI_DETAIL_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
protected:
	void
	push_front_widget(
		sge::gui::widget::reference
	);

	void
	pop_front_widget();

	void
	push_back_widget(
		sge::gui::widget::reference
	);

	void
	pop_back_widget();

	void
	replace_widgets(
		sge::gui::widget::reference_vector::size_type,
		sge::gui::widget::reference
	);

	void
	clear_widgets();
private:
	void
	insert_widget(
		sge::gui::widget::reference_vector::iterator,
		sge::gui::widget::reference
	);

	sge::gui::widget::reference_vector::iterator
	erase_widget(
		sge::gui::widget::reference_vector::iterator
	);

	void
	on_update(
		sge::gui::duration
	)
	override;

	void
	on_draw(
		sge::gui::renderer::base &, // NOLINT(google-runtime-references)
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	)
	override;

	sge::gui::get_focus
	on_click(
		sge::rucksack::vector const &
	)
	override;

	sge::gui::widget::optional_ref
	on_tab(
		sge::gui::widget::optional_focus_ref
	)
	override;

	void
	unregister(
		sge::gui::widget::base const &
	)
	override;

	enum class foreach_result
	{
		abort,
		continue_
	};

	template<
		typename Function
	>
	void
	foreach_widget(
		Function const &
	);

	sge::gui::context_ref const context_;

	sge::gui::widget::reference_vector widgets_;

	sge::rucksack::widget::reference const layout_;
};

}
}
}

#endif

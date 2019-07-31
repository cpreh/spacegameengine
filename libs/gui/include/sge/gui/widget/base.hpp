//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_BASE_HPP_INCLUDED
#define SGE_GUI_WIDGET_BASE_HPP_INCLUDED

#include <sge/font/char_type.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/focus_change_fwd.hpp>
#include <sge/gui/get_focus_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/optional_focus_fwd.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	SGE_GUI_DETAIL_SYMBOL
	virtual
	~base();

	virtual
	void
	on_update(
		sge::gui::duration
	);

	virtual
	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &
	) = 0;

	virtual
	sge::gui::get_focus
	on_click(
		sge::rucksack::vector
	);

	virtual
	void
	on_key(
		sge::input::key::code
	);

	virtual
	void
	on_char(
		sge::font::char_type
	);

	virtual
	void
	on_focus_changed(
		sge::gui::focus_change
	);

	virtual
	sge::gui::widget::optional_ref
	on_tab(
		sge::gui::widget::optional_focus &
	);

	virtual
	sge::rucksack::widget::base &
	layout() = 0;

	void
	parent(
		sge::gui::widget::optional_ref
	);

	SGE_GUI_DETAIL_SYMBOL
	void
	enable(
		bool
	);

	SGE_GUI_DETAIL_SYMBOL
	bool
	enabled() const;
private:
	virtual
	void
	unregister(
		sge::gui::widget::base const &
	);

	sge::gui::widget::optional_ref parent_;

	bool enabled_;
};

}
}
}

#endif

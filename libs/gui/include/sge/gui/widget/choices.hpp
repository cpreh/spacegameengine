//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_CHOICES_HPP_INCLUDED
#define SGE_GUI_WIDGET_CHOICES_HPP_INCLUDED

#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/index_callback.hpp>
#include <sge/gui/index_function.hpp>
#include <sge/gui/optional_index.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/choices_fwd.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class choices
:
	public sge::gui::widget::box_container
{
	FCPPT_NONMOVABLE(
		choices
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	choices(
		sge::gui::context_ref,
		sge::gui::style::const_reference,
		sge::renderer::device::ffp_ref,
		sge::font::object_ref,
		sge::gui::string_container &&,
		sge::gui::optional_index
	);

	SGE_GUI_DETAIL_SYMBOL
	~choices()
	override;

	[[nodiscard]]
	SGE_GUI_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	change(
		sge::gui::index_callback &&
	);

	[[nodiscard]]
	SGE_GUI_DETAIL_SYMBOL
	sge::gui::optional_index
	index() const;
private:
	void
	left_clicked();

	void
	right_clicked();

	template<
		typename Func
	>
	void
	update_index(
		Func const &
	);

	sge::gui::string_container const strings_;

	sge::gui::widget::button left_button_;

	sge::gui::widget::text middle_text_;

	sge::gui::widget::button right_button_;

	sge::gui::optional_index index_;

	fcppt::signal::auto_connection const left_connection_;

	fcppt::signal::auto_connection const right_connection_;

	using
	index_signal
	=
	fcppt::signal::object<
		sge::gui::index_function
	>;

	index_signal index_changed_;
};

}
}
}

#endif

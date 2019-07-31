//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_CONTEXT_HPP_INCLUDED
#define SGE_GUI_CONTEXT_HPP_INCLUDED

#include <sge/gui/context_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace gui
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	context();

	SGE_GUI_DETAIL_SYMBOL
	~context();

	void
	focus(
		sge::gui::widget::base &
	);

	void
	destroy(
		sge::gui::widget::base const &
	);

	sge::gui::widget::optional_ref
	focus() const;
private:
	sge::gui::widget::optional_ref focus_;
};

}
}

#endif

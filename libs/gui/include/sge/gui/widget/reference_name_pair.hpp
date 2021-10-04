//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_REFERENCE_NAME_PAIR_HPP_INCLUDED
#define SGE_GUI_WIDGET_REFERENCE_NAME_PAIR_HPP_INCLUDED

#include <sge/font/string.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_name_pair_fwd.hpp>


namespace sge::gui::widget
{

class reference_name_pair
{
public:
	SGE_GUI_DETAIL_SYMBOL
	reference_name_pair(
		sge::gui::widget::reference,
		sge::font::string &&
	);

	[[nodiscard]]
	sge::gui::widget::reference
	reference() const;

	[[nodiscard]]
	sge::font::string const &
	name() const;
private:
	sge::gui::widget::reference reference_;

	sge::font::string name_;
};

}

#endif

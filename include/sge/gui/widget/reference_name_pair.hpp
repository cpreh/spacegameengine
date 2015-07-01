#ifndef SGE_GUI_WIDGET_REFERENCE_NAME_PAIR_HPP_INCLUDED
#define SGE_GUI_WIDGET_REFERENCE_NAME_PAIR_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_name_pair_fwd.hpp>
#include <sge/font/string.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class reference_name_pair
{
public:
	SGE_GUI_DETAIL_SYMBOL
	reference_name_pair(
		sge::gui::widget::reference,
		sge::font::string const &
	);

	sge::gui::widget::reference const
	reference() const;

	sge::font::string const &
	name() const;
private:
	sge::gui::widget::reference reference_;

	sge::font::string name_;
};

}
}
}

#endif

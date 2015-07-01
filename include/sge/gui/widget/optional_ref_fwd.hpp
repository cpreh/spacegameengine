#ifndef SGE_GUI_WIDGET_OPTIONAL_REF_FWD_HPP_INCLUDED
#define SGE_GUI_WIDGET_OPTIONAL_REF_FWD_HPP_INCLUDED

#include <sge/gui/widget/base_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

typedef
fcppt::optional<
	sge::gui::widget::base &
>
optional_ref;

}
}
}

#endif

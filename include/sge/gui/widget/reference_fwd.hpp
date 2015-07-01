#ifndef SGE_GUI_WIDGET_REFERENCE_FWD_HPP_INCLUDED
#define SGE_GUI_WIDGET_REFERENCE_FWD_HPP_INCLUDED

#include <sge/gui/widget/base_fwd.hpp>
#include <fcppt/reference_wrapper_fwd.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

typedef
fcppt::reference_wrapper<
	sge::gui::widget::base
>
reference;

}
}
}

#endif

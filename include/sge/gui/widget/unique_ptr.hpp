#ifndef SGE_GUI_WIDGET_UNIQUE_PTR_HPP_INCLUDED
#define SGE_GUI_WIDGET_UNIQUE_PTR_HPP_INCLUDED

#include <sge/gui/widget/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

typedef
fcppt::unique_ptr<
	sge::gui::widget::base
>
unique_ptr;

}
}
}

#endif

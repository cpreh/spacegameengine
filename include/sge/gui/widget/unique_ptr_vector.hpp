#ifndef SGE_GUI_WIDGET_UNIQUE_PTR_VECTOR_HPP_INCLUDED
#define SGE_GUI_WIDGET_UNIQUE_PTR_VECTOR_HPP_INCLUDED

#include <sge/gui/widget/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

typedef
std::vector<
	sge::gui::widget::unique_ptr
>
unique_ptr_vector;

}
}
}

#endif

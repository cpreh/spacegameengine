#ifndef SGE_GUI_STYLE_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SGE_GUI_STYLE_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sge/gui/style/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace gui
{
namespace style
{

typedef
fcppt::unique_ptr<
	sge::gui::style::base
>
base_unique_ptr;

}
}
}

#endif

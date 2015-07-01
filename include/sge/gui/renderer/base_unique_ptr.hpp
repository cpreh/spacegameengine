#ifndef SGE_GUI_RENDERER_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SGE_GUI_RENDERER_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sge/gui/renderer/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace gui
{
namespace renderer
{

typedef
fcppt::unique_ptr<
	sge::gui::renderer::base
>
base_unique_ptr;

}
}
}

#endif

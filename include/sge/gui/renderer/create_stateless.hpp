#ifndef SGE_GUI_RENDERER_CREATE_STATELESS_HPP_INCLUDED
#define SGE_GUI_RENDERER_CREATE_STATELESS_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_unique_ptr.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>


namespace sge
{
namespace gui
{
namespace renderer
{

SGE_GUI_DETAIL_SYMBOL
sge::gui::renderer::base_unique_ptr
create_stateless(
	sge::renderer::device::ffp &
);

}
}
}

#endif

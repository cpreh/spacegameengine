#ifndef SGE_GUI_IMPL_MAKE_CONTAINER_PAIR_HPP_INCLUDED
#define SGE_GUI_IMPL_MAKE_CONTAINER_PAIR_HPP_INCLUDED

#include <sge/gui/impl/swap_pair.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>


namespace sge
{
namespace gui
{
namespace impl
{

sge::gui::widget::reference_alignment_vector
make_container_pair(
	sge::gui::widget::reference_alignment_pair const &,
	sge::gui::widget::reference_alignment_pair const &,
	sge::gui::impl::swap_pair
);

}
}
}

#endif

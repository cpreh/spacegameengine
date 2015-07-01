#include <sge/gui/impl/make_container_pair.hpp>
#include <sge/gui/impl/swap_pair.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>


sge::gui::widget::reference_alignment_vector
sge::gui::impl::make_container_pair(
	sge::gui::widget::reference_alignment_pair const &_first,
	sge::gui::widget::reference_alignment_pair const &_second,
	sge::gui::impl::swap_pair const _swap
)
{
	return
		_swap.get()
		?
			sge::gui::widget::reference_alignment_vector{
				_second,
				_first
			}
		:
			sge::gui::widget::reference_alignment_vector{
				_first,
				_second
			}
		;
}

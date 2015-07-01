#ifndef SGE_GUI_IMPL_STYLE_SPACING_HPP_INCLUDED
#define SGE_GUI_IMPL_STYLE_SPACING_HPP_INCLUDED

#include <sge/gui/impl/style/inner_border.hpp>
#include <sge/gui/impl/style/outer_border.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace gui
{
namespace impl
{
namespace style
{

typedef
std::integral_constant<
	sge::rucksack::scalar,
	(
		sge::gui::impl::style::inner_border::value
		+
		sge::gui::impl::style::outer_border::value
	)
	*
	2
>
spacing;

}
}
}
}

#endif

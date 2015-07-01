#ifndef SGE_GUI_IMPL_STYLE_INNER_BORDER_HPP_INCLUDED
#define SGE_GUI_IMPL_STYLE_INNER_BORDER_HPP_INCLUDED

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
	2
>
inner_border;

}
}
}
}

#endif

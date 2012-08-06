#ifndef SGE_RUCKSACK_WIDGET_OPTIONAL_PARENT_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_OPTIONAL_PARENT_HPP_INCLUDED

#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/optional_fwd.hpp>

namespace sge
{
namespace rucksack
{
namespace widget
{
typedef
fcppt::optional<sge::rucksack::widget::base &>
optional_parent;
}
}
}

#endif

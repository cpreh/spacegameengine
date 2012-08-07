#ifndef SGE_RUCKSACK_WIDGET_BOX_CHILD_INFORMATION_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_BOX_CHILD_INFORMATION_HPP_INCLUDED

#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/dim.hpp>
#include <fcppt/math/dim/object_impl.hpp>

namespace sge
{
namespace rucksack
{
namespace widget
{
namespace box
{
/**
 * This is a utility class which holds all the information needed for a child.
 * It's intentionally not supplied with SYMBOLs because it's not part of the
 * interface the user sees.
 */
class child_information
{
public:
	child_information();

	child_information(
		sge::rucksack::alignment::type,
		sge::rucksack::dim const &);

	sge::rucksack::alignment::type
	alignment() const;

	sge::rucksack::dim const &
	size() const;

	void
	size(
		sge::rucksack::dim const &);
private:
	sge::rucksack::alignment::type alignment_;
	sge::rucksack::dim size_;
};
}
}
}
}

#endif

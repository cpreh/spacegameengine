//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_MINIMUM_SIZE_HPP_INCLUDED
#define SGE_GUI_WIDGET_MINIMUM_SIZE_HPP_INCLUDED

#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/dummy.hpp>
#include <sge/gui/widget/minimum_size_fwd.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/minimum_size.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class minimum_size
:
	public sge::gui::widget::dummy
{
	FCPPT_NONMOVABLE(
		minimum_size
	);
public:
	explicit
	minimum_size(
		sge::gui::widget::reference
	);

	~minimum_size()
	override;

	sge::rucksack::widget::base &
	layout()
	override;
private:
	sge::rucksack::widget::minimum_size layout_;
};

}
}
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_MAIN_AREA_BASE_HPP_INCLUDED
#define SGE_GUI_MAIN_AREA_BASE_HPP_INCLUDED

#include <sge/gui/main_area/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace main_area
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();

	virtual
	~base();
public:
	virtual
	sge::gui::widget::base &
	widget() = 0;

	virtual
	void
	relayout() = 0;
};

}
}
}

#endif

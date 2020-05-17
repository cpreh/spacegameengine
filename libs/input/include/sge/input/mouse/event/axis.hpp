//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_MOUSE_EVENT_AXIS_HPP_INCLUDED
#define SGE_INPUT_MOUSE_EVENT_AXIS_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_code_fwd.hpp>
#include <sge/input/mouse/axis_value.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/axis_fwd.hpp>
#include <sge/input/mouse/event/base.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace input
{
namespace mouse
{
namespace event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL axis
:
	public sge::input::mouse::event::base
{
	FCPPT_NONMOVABLE(
		axis
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	axis(
		sge::input::mouse::shared_ptr,
		sge::input::mouse::axis const &,
		sge::input::mouse::axis_value
	);

	SGE_INPUT_DETAIL_SYMBOL
	~axis()
	override;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::mouse::axis const &
	get() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::mouse::axis_code
	code() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::mouse::axis_value
	value() const;
private:
	sge::input::mouse::axis const axis_;

	sge::input::mouse::axis_value const value_;
};

}
}
}
}

#endif

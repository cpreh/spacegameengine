//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_MOUSE_AXIS_INFO_HPP_INCLUDED
#define SGE_INPUT_MOUSE_AXIS_INFO_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_info_fwd.hpp>
#include <fcppt/optional_string.hpp>


namespace sge::input::mouse
{

class axis_info
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	axis_info(
		sge::input::mouse::axis_code,
		fcppt::optional_string &&
	);

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::mouse::axis_code
	code() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	fcppt::optional_string const &
	name() const;
private:
	sge::input::mouse::axis_code code_;

	fcppt::optional_string name_;
};

}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/scroll_value.hpp>
#include <sge/x11input/cursor/scroll_valuator.hpp>
#include <sge/x11input/device/valuator/any.hpp>
#include <sge/x11input/device/valuator/update.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::x11input::cursor::scroll_valuator::scroll_valuator(
	sge::x11input::device::valuator::any const &_any,
	sge::input::cursor::scroll_code const _code
)
:
	any_(
		_any
	),
	code_(
		_code
	)
{
}

sge::input::cursor::scroll_code
sge::x11input::cursor::scroll_valuator::code() const
{
	return
		code_;
}

sge::input::cursor::scroll_value
sge::x11input::cursor::scroll_valuator::update(
	sge::x11input::device::valuator::value const _value
)
{
	std::pair<
		sge::input::cursor::scroll_value,
		sge::x11input::device::valuator::any
	> const result(
		sge::x11input::device::valuator::update<
			sge::input::cursor::scroll_value
		>(
			any_,
			_value
		)
	);

	any_ =
		result.second;

	return
		result.first;
}

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_MOUSE_DEVICE_HPP_INCLUDED
#define SGE_INPUT_MOUSE_DEVICE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/input/mouse/info_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace input
{
namespace mouse
{

class SGE_CORE_DETAIL_CLASS_SYMBOL device
{
	FCPPT_NONCOPYABLE(
		device
	);
protected:
	SGE_INPUT_DETAIL_SYMBOL
	device();
public:
	SGE_INPUT_DETAIL_SYMBOL
	virtual
	~device();

	virtual
	sge::window::object &
	window() const = 0;

	virtual
	sge::input::mouse::info const &
	info() const = 0;
};

}
}
}

#endif

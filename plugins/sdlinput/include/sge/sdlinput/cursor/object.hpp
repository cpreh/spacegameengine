//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_SDLINPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/input/cursor/mode_fwd.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sdlinput
{
namespace cursor
{

class object
:
	public
		sge::input::cursor::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::window::object &
	);

	~object()
	override;

	sge::window::object &
	window() const
	override;

	sge::input::cursor::optional_position
	position() const
	override;

	void
	mode(
		sge::input::cursor::mode
	)
	override;
private:
	sge::window::object &window_;
};

}
}
}

#endif

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
#include <sge/window/object_ref.hpp>
#include <awl/backends/sdl/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::sdlinput::cursor
{

class object
:
	public
		sge::input::cursor::object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		sge::window::object_ref,
		awl::backends::sdl::window::object_ref
	);

	~object()
	override;

	[[nodiscard]]
	sge::window::object &
	window() const
	override;

	[[nodiscard]]
	sge::input::cursor::optional_position
	position() const
	override;

	void
	mode(
		sge::input::cursor::mode
	)
	override;
private:
	sge::window::object_ref const window_;

	awl::backends::sdl::window::object_ref const sdl_window_;
};

}

#endif

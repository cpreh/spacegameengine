//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_IMPL_CURSOR_RELATIVE_MOVEMENT_DETAIL_OBJECT_HPP_INCLUDED
#define SGE_INPUT_IMPL_CURSOR_RELATIVE_MOVEMENT_DETAIL_OBJECT_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/move_fwd.hpp>
#include <sge/input/cursor/relative_movement/difference_fwd.hpp>
#include <sge/input/cursor/relative_movement/detail/object_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/shared_ptr_std_hash.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace input
{
namespace cursor
{
namespace relative_movement
{
namespace detail
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::input::processor &
	);

	~object();
private:
	typedef
	fcppt::optional::object<
		sge::input::cursor::relative_movement::difference
	>
	optional_difference;

	awl::event::container
	on_event(
		awl::window::event::base const &
	);

	optional_difference
	update_pos(
		sge::input::cursor::event::move const &
	);

	typedef
	std::unordered_map<
		sge::input::cursor::shared_ptr,
		sge::input::cursor::optional_position
	>
	position_map;

	position_map positions_;

	fcppt::signal::auto_connection const connection_;
};

}
}
}
}
}

#endif

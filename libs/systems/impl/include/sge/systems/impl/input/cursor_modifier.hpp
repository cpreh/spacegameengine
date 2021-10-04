//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_INPUT_CURSOR_MODIFIER_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_INPUT_CURSOR_MODIFIER_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/impl/input/cursor_modifier_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge::systems::impl::input
{

class cursor_modifier
{
	FCPPT_NONMOVABLE(
		cursor_modifier
	);
public:
	cursor_modifier(
		sge::input::processor const &,
		sge::window::object_ref,
		sge::systems::cursor_option_field const &
	);

	~cursor_modifier();
private:
	[[nodiscard]]
	awl::event::container
	on_event(
		awl::window::event::base const &
	) const;

	sge::systems::cursor_option_field const options_;

	fcppt::signal::auto_connection const connection_;
};

}

#endif

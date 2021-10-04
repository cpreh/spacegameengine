//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_WINDOW_QUIT_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_QUIT_HPP_INCLUDED

#include <sge/systems/impl/window/quit_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/window/system_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge::systems::impl::window
{

class quit
{
	FCPPT_NONMOVABLE(
		quit
	);
public:
	quit(
		sge::window::system_ref,
		sge::window::object_ref
	);

	~quit();
private:
	sge::window::system_ref const system_;

	fcppt::signal::auto_connection const destroy_connection_;
};

}

#endif

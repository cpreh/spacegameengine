//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_WINDOW_QUIT_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_QUIT_HPP_INCLUDED

#include <sge/systems/impl/window/quit_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace window
{

class quit
{
	FCPPT_NONCOPYABLE(
		quit
	);
public:
	quit(
		sge::window::system &,
		sge::window::object &
	);

	~quit();
private:
	sge::window::system &system_;

	fcppt::signal::auto_connection const destroy_connection_;
};

}
}
}
}

#endif

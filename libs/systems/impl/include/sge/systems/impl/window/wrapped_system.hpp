//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_WINDOW_WRAPPED_SYSTEM_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_WRAPPED_SYSTEM_HPP_INCLUDED

#include <sge/systems/wrapped_window_fwd.hpp>
#include <sge/systems/impl/window/system_base.hpp>
#include <sge/window/system.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace window
{

class wrapped_system
:
	public sge::systems::impl::window::system_base
{
	FCPPT_NONMOVABLE(
		wrapped_system
	);
public:
	explicit
	wrapped_system(
		sge::systems::wrapped_window const &
	);

	~wrapped_system()
	override;
private:
	[[nodiscard]]
	sge::window::system &
	get()
	override;

	sge::window::system system_;
};

}
}
}
}

#endif

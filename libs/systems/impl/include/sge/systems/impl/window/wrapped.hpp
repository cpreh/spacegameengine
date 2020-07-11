//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_WINDOW_WRAPPED_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_WRAPPED_HPP_INCLUDED

#include <sge/systems/wrapped_window_fwd.hpp>
#include <sge/systems/impl/window/base.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace window
{

class wrapped
:
	public sge::systems::impl::window::base
{
	FCPPT_NONMOVABLE(
		wrapped
	);
public:
	wrapped(
		sge::systems::wrapped_window const &,
		sge::window::system_ref
	);

	~wrapped()
	override;
private:
	[[nodiscard]]
	sge::window::object &
	get() const
	override;

	mutable sge::window::object window_;
};

}
}
}
}

#endif

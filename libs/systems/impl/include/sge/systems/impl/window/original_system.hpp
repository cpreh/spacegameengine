//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_WINDOW_ORIGINAL_SYSTEM_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_ORIGINAL_SYSTEM_HPP_INCLUDED

#include <sge/systems/impl/window/system_base.hpp>
#include <sge/window/system.hpp>
#include <awl/system/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace window
{

class original_system
:
	public sge::systems::impl::window::system_base
{
	FCPPT_NONCOPYABLE(
		original_system
	);
public:
	explicit
	original_system(
		fcppt::log::context &
	);

	~original_system()
	override;
private:
	sge::window::system &
	get()
	override;

	awl::system::object_unique_ptr const awl_system_;

	sge::window::system system_;
};

}
}
}
}

#endif

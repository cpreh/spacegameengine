//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_WINDOW_ORIGINAL_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_ORIGINAL_HPP_INCLUDED

#include <sge/systems/original_window_fwd.hpp>
#include <sge/systems/impl/renderer/optional_system_ref_fwd.hpp>
#include <sge/systems/impl/window/base.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/cursor/object_unique_ptr.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace window
{

class original
:
	public sge::systems::impl::window::base
{
	FCPPT_NONCOPYABLE(
		original
	);
public:
	original(
		sge::systems::original_window const &,
		sge::window::system &,
		sge::systems::impl::renderer::optional_system_ref const &
	);

	~original()
	override;
private:
	sge::window::object &
	get() const
	override;

	awl::visual::object_unique_ptr const awl_visual_;

	awl::cursor::object_unique_ptr const awl_cursor_;

	awl::window::object_unique_ptr const awl_window_;

	mutable sge::window::object window_;
};

}
}
}
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_WINDOW_OBJECT_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_OBJECT_HPP_INCLUDED

#include <sge/systems/window_fwd.hpp>
#include <sge/systems/impl/renderer/optional_system_ref.hpp>
#include <sge/systems/impl/window/base_unique_ptr.hpp>
#include <sge/systems/impl/window/object_fwd.hpp>
#include <sge/systems/impl/window/quit_fwd.hpp>
#include <sge/systems/impl/window/system_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace window
{

class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		sge::systems::window const &,
		sge::systems::impl::window::system const &,
		sge::systems::impl::renderer::optional_system_ref const &
	);

	~object();

	[[nodiscard]]
	sge::window::object &
	get() const;

	void
	post_init() const;
private:
	sge::systems::impl::window::base_unique_ptr const base_;

	bool const show_on_post_;

	using
	quit_unique_ptr
	=
	fcppt::unique_ptr<
		sge::systems::impl::window::quit
	>;

	using
	optional_quit_unique_ptr
	=
	fcppt::optional::object<
		quit_unique_ptr
	>;

	optional_quit_unique_ptr const quit_;
};

}
}
}
}

#endif

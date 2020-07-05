//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_ANY_VISITOR_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_ANY_VISITOR_HPP_INCLUDED

#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/config_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/detail/instance_impl_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace systems
{
namespace impl
{

class any_visitor
{
public:
	explicit
	any_visitor(
		fcppt::reference<
			sge::systems::detail::instance_impl
		>
	);

	void
	operator()(
		sge::systems::config const &
	) const;

	void
	operator()(
		sge::systems::detail::renderer const &
	) const;

	void
	operator()(
		sge::systems::window const &
	) const;

	void
	operator()(
		sge::systems::image2d const &
	) const;

	void
	operator()(
		sge::systems::audio_loader const &
	) const;

	void
	operator()(
		sge::systems::audio_player const &
	) const;

	void
	operator()(
		sge::systems::input const &
	) const;

	void
	operator()(
		sge::systems::font const &
	) const;
private:
	fcppt::reference<
		sge::systems::detail::instance_impl
	> impl_;
};

}
}
}

#endif

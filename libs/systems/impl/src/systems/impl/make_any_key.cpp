//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_key.hpp>
#include <sge/systems/impl/make_any_key.hpp>
#include <fcppt/variant/apply.hpp>


namespace
{

struct make_key_visitor
{
#define SGE_SYSTEMS_MAKE_KEY_CASE(\
	type,\
	name\
)\
	sge::systems::detail::any_key \
	operator()( \
		sge::systems::type const & \
	) const \
	{ \
		return \
			sge::systems::detail::any_key::name;\
	}

	SGE_SYSTEMS_MAKE_KEY_CASE(
		config,
		config
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		window,
		window
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		detail::renderer,
		renderer
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		image2d,
		image2d
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		audio_loader,
		audio_loader
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		audio_player,
		audio_player
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		input,
		input
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		font,
		font
	)
};

}

sge::systems::detail::any_key
sge::systems::impl::make_any_key(
	sge::systems::detail::any const &_any
)
{
	return
		fcppt::variant::apply(
			::make_key_visitor(),
			_any
		);
}

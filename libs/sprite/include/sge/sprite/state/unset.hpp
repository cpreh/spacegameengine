//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_UNSET_HPP_INCLUDED
#define SGE_SPRITE_STATE_UNSET_HPP_INCLUDED

#include <sge/sprite/state/options_impl.hpp>
#include <sge/sprite/state/detail/unset_one.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

template<
	typename RenderContext,
	typename StateChoices
>
void
unset(
	RenderContext &_render_context,
	sge::sprite::state::options<
		StateChoices
	> const &_options
)
{
	fcppt::algorithm::loop(
		typename
		StateChoices::optional_elements{},
		sge::sprite::state::detail::unset_one<
			StateChoices
		>(
			fcppt::make_ref(
				_render_context
			),
			fcppt::make_cref(
				_options.elements()
			)
		)
	);
}

}
}
}

#endif

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_SPRITE_DETAIL_RENDER_SCOPED_STATES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SCOPED_STATES_HPP_INCLUDED

#include <sge/sprite/state/render_context.hpp>
#include <sge/sprite/state/options_fwd.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/detail/set_one.hpp>
#include <sge/sprite/state/detail/unset_one.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/mpl/for_each.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	typename StateChoices
>
class scoped_states
{
	FCPPT_NONCOPYABLE(
		scoped_states
	);
public:
	typedef typename sge::sprite::state::render_context<
		StateChoices
	>::type render_context;

	typedef sge::sprite::state::options<
		StateChoices
	> state_options;

	typedef sge::sprite::state::object<
		StateChoices
	> state_object;

	scoped_states(
		render_context &_render_context,
		state_options const &_options,
		state_object const &_object
	)
	:
		render_context_(
			_render_context
		),
		options_(
			_options
		),
		object_(
			_object
		)
	{
		fcppt::mpl::for_each<
			typename StateChoices::optional_elements
		>(
			sge::sprite::state::detail::set_one<
				StateChoices
			>(
				render_context_,
				options_.elements(),
				object_.elements()
			)
		);
	}

	~scoped_states()
	{
		fcppt::mpl::for_each<
			typename StateChoices::optional_elements
		>(
			sge::sprite::state::detail::unset_one<
				StateChoices
			>(
				render_context_,
				options_.elements()
			)
		);
	}
private:
	render_context &render_context_;

	state_options const &options_;

	state_object const &object_;
};

}
}
}
}

#endif

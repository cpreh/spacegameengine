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


#ifndef SGE_SPRITE_STATE_DETAIL_MAKE_VIEWPORT_MANAGER_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_MAKE_VIEWPORT_MANAGER_HPP_INCLUDED

#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/sprite/state/needs_viewport_manager.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <sge/sprite/state/detail/viewport_manager_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
typename boost::enable_if<
	sge::sprite::state::needs_viewport_manager<
		StateChoices
	>,
	fcppt::unique_ptr<
		sge::sprite::state::detail::viewport_manager<
			StateChoices
		>
	>
>::type
make_viewport_manager(
	typename sge::sprite::state::detail::object_class<
		StateChoices
	>::type &_elements,
	sge::renderer::device::ffp &_renderer,
	sge::sprite::state::parameters<
		StateChoices
	> const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sge::sprite::state::detail::viewport_manager<
				StateChoices
			>
		>(
			fcppt::ref(
				_elements
			),
			fcppt::ref(
				_renderer
			),
			fcppt::ref(
				*_parameters.viewport_manager()
			)
		);
}

template<
	typename StateChoices,
	typename Renderer
>
typename boost::disable_if<
	sge::sprite::state::needs_viewport_manager<
		StateChoices
	>,
	fcppt::unique_ptr<
		sge::sprite::state::detail::viewport_manager<
			StateChoices
		>
	>
>::type
make_viewport_manager(
	typename sge::sprite::state::detail::object_class<
		StateChoices
	>::type &,
	Renderer &,
	sge::sprite::state::parameters<
		StateChoices
	> const &
)
{
	return
		fcppt::unique_ptr<
			sge::sprite::state::detail::viewport_manager<
				StateChoices
			>
		>();
}

}
}
}
}

#endif

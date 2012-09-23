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


#ifndef SGE_SPRITE_STATE_DETAIL_VIEWPORT_MANAGER_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_VIEWPORT_MANAGER_IMPL_HPP_INCLUDED

#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/sprite/state/with_transform.hpp>
#include <sge/sprite/state/detail/viewport_manager_decl.hpp>
#include <sge/sprite/state/roles/transform.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

template<
	typename StateChoices
>
sge::sprite::state::detail::viewport_manager<
	StateChoices
>::viewport_manager(
	object_class &_objects,
	sge::renderer::device::ffp &_renderer,
	sge::viewport::manager &_manager
)
:
	objects_(
		_objects
	),
	renderer_(
		_renderer
	),
	resize_connection_(
		_manager.manage_callback(
			std::tr1::bind(
				&viewport_manager::on_manage,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
}

FCPPT_PP_POP_WARNING

template<
	typename StateChoices
>
sge::sprite::state::detail::viewport_manager<
	StateChoices
>::~viewport_manager()
{
}

template<
	typename StateChoices
>
void
sge::sprite::state::detail::viewport_manager<
	StateChoices
>::on_manage(
	sge::renderer::target::viewport const &_viewport
)
{
	objects_. template set<
		sge::sprite::state::roles::transform
	>(
		fcppt::shared_ptr<
			sge::renderer::state::ffp::transform::object
		>(
			sge::sprite::state::with_transform::make(
				renderer_,
				sge::sprite::state::with_transform::optional_extra_parameters(
					_viewport
				)
			)
		)
	);
}

#endif

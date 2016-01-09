/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/viewport/adaptor.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_wrapper.hpp>
#include <fcppt/reference_wrapper_to_base.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::rucksack::viewport::adaptor::adaptor(
	sge::viewport::manager &_viewport,
	sge::renderer::device::core &_renderer
)
:
	sge::rucksack::widget::base(),
	target_(
		_renderer.onscreen_target()
	),
	child_(),
	viewport_connection_(
		_viewport.manage_callback(
			sge::viewport::manage_callback{
				std::bind(
					&sge::rucksack::viewport::adaptor::manage_callback,
					this
				)
			}
		)
	)
{
}

FCPPT_PP_POP_WARNING

void
sge::rucksack::viewport::adaptor::size(
	sge::rucksack::dim const &_size
)
{
	target_.viewport(
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect(
				target_.viewport().get().pos(),
				fcppt::math::dim::structure_cast<
					sge::renderer::pixel_rect::dim,
					fcppt::cast::size_fun
				>(
					_size
				)
			)
		)
	);
}

void
sge::rucksack::viewport::adaptor::position(
	sge::rucksack::vector const &_pos
)
{
	target_.viewport(
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect(
				fcppt::math::vector::structure_cast<
					sge::renderer::pixel_rect::vector,
					fcppt::cast::size_fun
				>(
					_pos
				),
				target_.viewport().get().size()
			)
		)
	);
}

sge::rucksack::dim
sge::rucksack::viewport::adaptor::size() const
{
	return
		fcppt::math::dim::structure_cast<
			sge::rucksack::dim,
			fcppt::cast::size_fun
		>(
			target_.viewport().get().size()
		);
}

sge::rucksack::vector
sge::rucksack::viewport::adaptor::position() const
{
	return
		fcppt::math::vector::structure_cast<
			sge::rucksack::vector,
			fcppt::cast::size_fun
		>(
			target_.viewport().get().pos()
		);
}

sge::rucksack::axis_policy2
sge::rucksack::viewport::adaptor::axis_policy() const
{
	// A dummy for now, until there's a use case
	return
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					sge::rucksack::scalar()
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					sge::rucksack::scalar()
				}
			}
		};
}

void
sge::rucksack::viewport::adaptor::relayout()
{
	fcppt::optional::maybe_void(
		child_,
		[
			this
		](
			fcppt::reference_wrapper<
				sge::rucksack::widget::base
			> const _child
		)
		{
			this->resize_child();

			_child.get().relayout();
		}
	);
}

void
sge::rucksack::viewport::adaptor::child(
	sge::rucksack::widget::base &_new_child
)
{
	fcppt::optional::maybe_void(
		child_,
		[](
			fcppt::reference_wrapper<
				sge::rucksack::widget::base
			> const _child
		)
		{
			_child.get().parent(
				sge::rucksack::widget::optional_ref()
			);
		}
	);

	child_ =
		sge::rucksack::widget::optional_ref(
			fcppt::make_ref(
				_new_child
			)
		);

	_new_child.parent(
		sge::rucksack::widget::optional_ref(
			fcppt::reference_wrapper_to_base<
				sge::rucksack::widget::base
			>(
				fcppt::make_ref(
					*this
				)
			)
		)
	);

	this->resize_child();
}


sge::rucksack::viewport::adaptor::~adaptor()
{
	fcppt::optional::maybe_void(
		child_,
		[](
			fcppt::reference_wrapper<
				sge::rucksack::widget::base
			> const _child
		)
		{
			_child.get().parent(
				sge::rucksack::widget::optional_ref()
			);
		}
	);
}

void
sge::rucksack::viewport::adaptor::manage_callback()
{
	if(
		child_.has_value()
	)
		this->resize_child();
}

void
sge::rucksack::viewport::adaptor::resize_child()
{
	sge::rucksack::widget::base &cur_child(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			child_
		).get()
	);

	cur_child.position(
		fcppt::math::vector::null<
			sge::rucksack::vector
		>()
	);

	cur_child.size(
		this->size()
	);

	cur_child.relayout();
}

void
sge::rucksack::viewport::adaptor::child_destroyed(
	sge::rucksack::widget::base &_child
)
{
	FCPPT_ASSERT_PRE(
		sge::rucksack::widget::optional_ref(
			fcppt::make_ref(
				_child
			)
		)
		==
		child_
	);

	child_ =
		sge::rucksack::widget::optional_ref();
}

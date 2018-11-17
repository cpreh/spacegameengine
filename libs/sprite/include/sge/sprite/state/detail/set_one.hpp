/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_STATE_DETAIL_SET_ONE_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_SET_ONE_HPP_INCLUDED

#include <sge/sprite/state/render_context.hpp>
#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <sge/sprite/state/detail/options_class.hpp>
#include <fcppt/not.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/tag.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/set.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
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
class set_one
{
public:
	typedef
	sge::sprite::state::detail::object_class<
		StateChoices
	>
	object_class;

	typedef
	sge::sprite::state::detail::options_class<
		StateChoices
	>
	options_class;

	typedef
	sge::sprite::state::render_device<
		StateChoices
	>
	render_device;

	typedef
	sge::sprite::state::render_context<
		StateChoices
	>
	render_context;

	set_one(
		render_device &_render_device,
		render_context &_render_context,
		options_class const &_options,
		object_class &_objects
	)
	:
		render_device_(
			_render_device
		),
		render_context_(
			_render_context
		),
		options_(
			_options
		),
		objects_(
			_objects
		)
	{
	}

	typedef
	void
	result_type;

	template<
		typename Type
	>
	std::enable_if_t<
		Type::persistent::value,
		result_type
	>
	operator()(
		fcppt::tag<
			Type
		>
	) const
	{
		// TODO: Move this somewhere else
		if(
			!fcppt::record::get<
				typename
				Type::role
			>(
				options_.get()
			)
		)
			return;

		Type::set(
			render_context_.get(),
			*fcppt::record::get<
				typename
				Type::role
			>(
				objects_.get()
			)
		);
	}

	template<
		typename Type
	>
	std::enable_if_t<
		fcppt::not_(
			Type::persistent::value
		),
		result_type
	>
	operator()(
		fcppt::tag<
			Type
		>
	) const
	{
		if(
			!fcppt::record::get<
				typename
				Type::role
			>(
				options_.get()
			)
		)
			return;

		// This should be more generic, but it will do for transform
		// for now
		// TODO: Check if the state has options or not
		fcppt::record::set<
			typename
			Type::role
		>(
			objects_.get(),
			Type::make(
				render_device_.get(),
				render_context_.get(),
				fcppt::record::get<
					typename
					Type::option_role
				>(
					options_.get()
				)
			)
		);

		fcppt::optional::maybe_void(
			fcppt::record::get<
				typename
				Type::role
			>(
				objects_.get()
			),
			[
				this
			](
				typename
				Type::state_type const &_state
			)
			{
				Type::set(
					render_context_.get(),
					*_state
				);
			}
		);
	}
private:
	fcppt::reference<
		render_device
	> render_device_;

	fcppt::reference<
		render_context
	> render_context_;

	fcppt::reference<
		options_class const
	> options_;

	fcppt::reference<
		object_class
	> objects_;
};

}
}
}
}

#endif

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


#ifndef SGE_SPRITE_STATE_DETAIL_SET_ONE_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_SET_ONE_HPP_INCLUDED

#include <sge/sprite/state/render_context.hpp>
#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <sge/sprite/state/detail/options_class.hpp>
#include <majutsu/get.hpp>
#include <majutsu/set.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
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
	FCPPT_NONASSIGNABLE(
		set_one
	);
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

	typedef void result_type;

	template<
		typename Type
	>
	typename boost::enable_if<
		typename Type::persistent,
		result_type
	>::type
	operator()() const
	{
		if(
			!majutsu::get<
				typename Type::role
			>(
				options_
			)
		)
			return;

		Type::set(
			render_context_,
			*majutsu::get<
				typename Type::role
			>(
				objects_
			)
		);
	}

	template<
		typename Type
	>
	typename boost::disable_if<
		typename Type::persistent,
		result_type
	>::type
	operator()() const
	{
		if(
			!majutsu::get<
				typename Type::role
			>(
				options_
			)
		)
			return;

		typedef
		fcppt::unique_ptr<
			typename Type::state_type
		>
		state_unique_ptr;

		// This should be more generic, but it will do for transform
		// for now
		fcppt::maybe_void(
			// TODO: Check if the state has options or not
			Type::make(
				render_device_,
				render_context_,
				majutsu::get<
					typename Type::option_role
				>(
					options_
				)
			),
			[
				this
			](
				state_unique_ptr &&_state
			)
			{
				// TODO: Make this movable
				typedef
				fcppt::shared_ptr<
					typename Type::state_type
				>
				state_shared_ptr;

				state_shared_ptr const shared_state(
					std::move(
						_state
					)
				);

				majutsu::set<
					typename Type::role
				>(
					objects_,
					shared_state
				);

				Type::set(
					render_context_,
					*shared_state
				);
			}
		);
	}
private:
	render_device &render_device_;

	render_context &render_context_;

	options_class const &options_;

	object_class &objects_;
};

}
}
}
}

#endif

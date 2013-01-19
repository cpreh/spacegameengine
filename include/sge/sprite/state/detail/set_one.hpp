/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <fcppt/nonassignable.hpp>
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
class set_one
{
	FCPPT_NONASSIGNABLE(
		set_one
	);
public:
	typedef typename sge::sprite::state::detail::object_class<
		StateChoices
	>::type object_class;

	typedef typename sge::sprite::state::detail::options_class<
		StateChoices
	>::type options_class;

	typedef typename sge::sprite::state::render_device<
		StateChoices
	>::type render_device;

	typedef typename sge::sprite::state::render_context<
		StateChoices
	>::type render_context;

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
			!options_. template get<
				typename Type::role
			>()
		)
			return;

		Type::set(
			render_context_,
			*objects_. template get<
				typename Type::role
			>()
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
			!options_. template get<
				typename Type::role
			>()
		)
			return;

		typedef fcppt::shared_ptr<
			typename Type::state_type
		> state_shared_ptr;

		// This should be more generic, but it will do for transform
		// for now
		state_shared_ptr const object(
			Type::make(
				render_device_,
				render_context_
			)
		);

		if(
			!object
		)
			return;

		objects_. template set<
			typename Type::role
		>(
			object
		);

		Type::set(
			render_context_,
			*object
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

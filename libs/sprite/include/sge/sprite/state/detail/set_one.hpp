//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_SET_ONE_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_SET_ONE_HPP_INCLUDED

#include <sge/sprite/state/render_context.hpp>
#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/device_for_state.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <sge/sprite/state/detail/options_class.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/not.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
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
	using
	object_class
	=
	sge::sprite::state::detail::object_class<
		StateChoices
	>;

	using
	options_class
	=
	sge::sprite::state::detail::options_class<
		StateChoices
	>;

	using
	render_device
	=
	sge::sprite::state::render_device<
		StateChoices
	>;

	using
	render_context
	=
	sge::sprite::state::render_context<
		StateChoices
	>;

	set_one(
		fcppt::reference<
			render_device
		> const _render_device,
		fcppt::reference<
			render_context
		> const _render_context,
		fcppt::reference<
			options_class const
		> const _options,
		fcppt::reference<
			object_class
		> const _objects
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

	template<
		typename Type
	>
	std::enable_if_t<
		Type::persistent::value,
		void
	>
	operator()(
		fcppt::tag<
			Type
		>
	) const
	{
		// TODO(philipp): Move this somewhere else
		if(
			!fcppt::record::get<
				typename
				Type::role
			>(
				options_.get()
			)
		)
		{
			return;
		}

		Type::set(
			render_context_.get(),
			fcppt::make_cref(
				*fcppt::record::get<
					typename
					Type::role
				>(
					objects_.get()
				)
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
		void
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
		{
			return;
		}

		// This should be more generic, but it will do for transform
		// for now
		// TODO(philipp): Check if the state has options or not
		fcppt::record::set<
			typename
			Type::role
		>(
			objects_.get(),
			Type::make(
				fcppt::reference_to_base<
					sge::sprite::state::detail::device_for_state<
						Type
					>
				>(
					render_device_
				),
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
					fcppt::make_cref(
						*_state
					)
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

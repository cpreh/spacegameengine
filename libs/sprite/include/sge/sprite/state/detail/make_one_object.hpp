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


#ifndef SGE_SPRITE_STATE_DETAIL_MAKE_ONE_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_MAKE_ONE_OBJECT_HPP_INCLUDED

#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/parameters_class.hpp>
#include <fcppt/not.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/find.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/front.hpp>
#include <brigand/types/args.hpp>
#include <type_traits>
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
class make_one_object
{
public:
	typedef
	sge::sprite::state::render_device<
		StateChoices
	>
	render_device;

	typedef
	sge::sprite::state::detail::parameters_class<
		StateChoices
	>
	parameters_class;

	make_one_object(
		render_device &_render_device,
		parameters_class const &_parameters
	)
	:
		render_device_(
			_render_device
		),
		parameters_(
			_parameters
		)
	{
	}
private:
	template<
		typename State,
		typename Role
	>
	struct state_has_role
	:
	std::is_same<
		typename
		State::role,
		Role
	>
	{
	};

	template<
		typename Role
	>
	using
	state_for_role
	=
	brigand::front<
		brigand::find<
			typename
			StateChoices::optional_elements,
			brigand::bind<
				state_has_role,
				brigand::_1,
				brigand::pin<
					Role
				>
			>
		>
	>;
public:
	template<
		typename Type,
		typename Role
	>
	std::enable_if_t<
		state_for_role<
			Role
		>::persistent::value,
		typename
		state_for_role<
			Role
		>::state_type
	>
	operator()(
		fcppt::record::element<
			Role,
			Type
		>
	) const
	{
		return
			state_for_role<
				Role
			>::make(
				render_device_.get(),
				fcppt::record::get<
					typename
					state_for_role<
						Role
					>::parameter_role
				>(
					parameters_.get()
				)
			);
	}

	template<
		typename Type,
		typename Role
	>
	std::enable_if_t<
		fcppt::not_(
			state_for_role<
				Role
			>::persistent::value
		),
		fcppt::optional::object<
			typename
			state_for_role<
				Role
			>::state_type
		>
	>
	operator()(
		fcppt::record::element<
			Role,
			Type
		>
	) const
	{
		return
			fcppt::optional::object<
				typename
				state_for_role<
					Role
				>::state_type
			>();
	}
private:
	fcppt::reference<
		render_device
	> render_device_;

	fcppt::reference<
		parameters_class const
	> parameters_;
};

}
}
}
}

#endif

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
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/placeholders.hpp>
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
class make_one_object
{
	FCPPT_NONASSIGNABLE(
		make_one_object
	);
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
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

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

	FCPPT_PP_POP_WARNING

	template<
		typename Role
	>
	using
	state_for_role
	=
	typename
	boost::mpl::deref<
		typename
		boost::mpl::find_if<
			typename
			StateChoices::optional_elements,
			state_has_role<
				boost::mpl::_1,
				Role
			>
		>::type
	>::type;
public:
	template<
		typename Type,
		typename Role
	>
	typename
	boost::enable_if<
		typename
		state_for_role<
			Role
		>::persistent,
		typename
		state_for_role<
			Role
		>::state_type
	>::type
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
				render_device_,
				fcppt::record::get<
					typename
					state_for_role<
						Role
					>::parameter_role
				>(
					parameters_
				)
			);
	}

	template<
		typename Type,
		typename Role
	>
	typename
	boost::disable_if<
		typename
		state_for_role<
			Role
		>::persistent,
		fcppt::optional::object<
			typename
			state_for_role<
				Role
			>::state_type
		>
	>::type
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
	render_device &render_device_;

	parameters_class const &parameters_;
};

}
}
}
}

#endif

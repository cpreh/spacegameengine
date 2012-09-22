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


#ifndef SGE_SPRITE_STATE_DETAIL_MAKE_ONE_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_MAKE_ONE_OBJECT_HPP_INCLUDED

#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <sge/sprite/state/detail/parameters_class.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/shared_ptr_impl.hpp>


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
	typedef typename sge::sprite::state::detail::object_class<
		StateChoices
	>::type object_class;

	typedef typename sge::sprite::state::render_device<
		StateChoices
	>::type render_device;

	typedef typename sge::sprite::state::detail::parameters_class<
		StateChoices
	>::type parameters_class;

	make_one_object(
		object_class &_result,
		render_device &_render_device,
		parameters_class const &_parameters
	)
	:
		result_(
			_result
		),
		render_device_(
			_render_device
		),
		parameters_(
			_parameters
		)
	{
	}

	typedef void result_type;

	template<
		typename Type
	>
	result_type
	operator()() const
	{
		result_. template set<
			typename Type::role
		>(
			fcppt::shared_ptr<
				typename Type::state_type
			>(
				Type::make(
					render_device_,
					parameters_. template get<
						typename Type::parameter_role
					>()
				)
			)
		);
	}
private:
	object_class &result_;

	render_device &render_device_;

	parameters_class const &parameters_;
};

}
}
}
}

#endif

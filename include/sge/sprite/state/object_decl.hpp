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


#ifndef SGE_SPRITE_STATE_OBJECT_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_OBJECT_DECL_HPP_INCLUDED

#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/parameters_fwd.hpp>
#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

template<
	typename StateChoices
>
class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef StateChoices state_choices;

	typedef
	sge::sprite::state::detail::object_class<
		StateChoices
	>
	elements_type;

	typedef
	sge::sprite::state::parameters<
		state_choices
	>
	parameters_type;

	typedef
	sge::sprite::state::render_device<
		StateChoices
	>
	render_device;

	object(
		render_device &,
		parameters_type const &
	);

	~object();

	elements_type &
	elements();

	elements_type const &
	elements() const;

	render_device &
	renderer() const;
private:
	render_device &renderer_;

	elements_type elements_;
};

}
}
}

#endif

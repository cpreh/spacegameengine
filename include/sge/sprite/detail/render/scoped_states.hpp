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


#ifndef SGE_SPRITE_DETAIL_RENDER_SCOPED_STATES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SCOPED_STATES_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/sprite/detail/render/states.hpp>
#include <sge/sprite/render/state_options.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	typename Choices,
	sge::sprite::render::state_options::type Options
>
class scoped_states;

template<
	typename Choices
>
class scoped_states<
	Choices,
	sge::sprite::render::state_options::set
>
{
	FCPPT_NONCOPYABLE(
		scoped_states
	);
public:
	explicit
	scoped_states(
		sge::renderer::device &_device
	)
	:
		states_(
			_device,
			sge::sprite::detail::render::states<
				Choices
			>::value
		)
	{
	}

	~scoped_states()
	{
	}
private:
	sge::renderer::state::scoped const states_;
};


template<
	typename Choices
>
class scoped_states<
	Choices,
	sge::sprite::render::state_options::nothing
>
{
	FCPPT_NONCOPYABLE(
		scoped_states
	);
public:
	scoped_states(
		sge::renderer::device &
	)
	{
	}

	~scoped_states()
	{
	}
};

}
}
}
}

#endif

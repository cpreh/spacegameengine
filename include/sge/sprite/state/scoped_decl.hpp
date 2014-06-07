/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_STATE_SCOPED_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_SCOPED_DECL_HPP_INCLUDED

#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_fwd.hpp>
#include <sge/sprite/state/render_context.hpp>
#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/scoped_fwd.hpp>
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
class scoped
{
	FCPPT_NONCOPYABLE(
		scoped
	);
public:
	typedef typename sge::sprite::state::render_device<
		StateChoices
	>::type render_device;

	typedef typename sge::sprite::state::render_context<
		StateChoices
	>::type render_context;

	typedef sge::sprite::state::options<
		StateChoices
	> state_options;

	typedef sge::sprite::state::object<
		StateChoices
	> state_object;

	scoped(
		render_device &,
		render_context &,
		state_options const &,
		state_object &
	);

	~scoped();
private:
	render_context &render_context_;

	state_options const &options_;
};

}
}
}

#endif

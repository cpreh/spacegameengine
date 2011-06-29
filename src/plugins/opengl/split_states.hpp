/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_SPLIT_STATES_HPP_INCLUDED
#define SGE_OPENGL_SPLIT_STATES_HPP_INCLUDED

#include "split_states_fwd.hpp"
#include "common.hpp"
#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class split_states
{
	FCPPT_NONCOPYABLE(
		split_states
	);
public:
	explicit split_states(
		renderer::state::list &
	);

	~split_states();

	void
	update_stencil_func(
		renderer::depth_stencil_buffer::type
	);

	void
	update_stencil_op();

	void
	update_blend();

	void
	update_alpha_test();

	void
	update_write_color_buffer();
private:
	template<
		typename T
	>
	T const
	get(
		T const &
	) const;

	renderer::state::list &states_;
};

}
}

#endif

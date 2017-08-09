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


#ifndef SGE_RENDERER_EVENT_RENDER_HPP_INCLUDED
#define SGE_RENDERER_EVENT_RENDER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/event/base.hpp>
#include <sge/renderer/event/render_fwd.hpp>
#include <awl/window/reference.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL render
:
	public sge::renderer::event::base
{
	FCPPT_NONCOPYABLE(
		render
	);
public:
	// TODO: Which parameters do we want?
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	render(
		awl::window::reference
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~render()
	override;
};

}
}
}

#endif

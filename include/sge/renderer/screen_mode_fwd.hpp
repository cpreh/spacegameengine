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


#ifndef SGE_RENDERER_SCREEN_MODE_FWD_HPP_INCLUDED
#define SGE_RENDERER_SCREEN_MODE_FWD_HPP_INCLUDED

#include <sge/renderer/fullscreen_fwd.hpp>
#include <sge/renderer/windowed_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{

/**
\brief A variant over two possible screen modes

A screen mode is either windowed, which is represented by an
sge::renderer::windowed parameter, or it is fullscreen, which is represented by
an sge::renderer::fullscreen parameter.
*/
typedef fcppt::variant::object<
	boost::mpl::vector2<
		sge::renderer::fullscreen,
		sge::renderer::windowed
	>
> screen_mode;

}
}

#endif

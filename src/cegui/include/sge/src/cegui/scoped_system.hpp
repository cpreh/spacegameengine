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


#ifndef SGE_SRC_CEGUI_SCOPED_SYSTEM_HPP_INCLUDED
#define SGE_SRC_CEGUI_SCOPED_SYSTEM_HPP_INCLUDED

#include <sge/src/cegui/image_codec_fwd.hpp>
#include <sge/src/cegui/renderer_fwd.hpp>
#include <sge/src/cegui/resource_provider_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace cegui
{

class scoped_system
{
	FCPPT_NONCOPYABLE(
		scoped_system
	);
public:
	scoped_system(
		sge::cegui::renderer &,
		sge::cegui::image_codec &,
		sge::cegui::resource_provider &
	);

	~scoped_system();
};

}
}

#endif

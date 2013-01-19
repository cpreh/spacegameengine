/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_CEGUI_BATCH_HPP_INCLUDED
#define SGE_SRC_CEGUI_BATCH_HPP_INCLUDED

#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/vertex/buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/src/cegui/batch_fwd.hpp>
#include <sge/src/cegui/clip.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace cegui
{

class batch
{
	FCPPT_NONCOPYABLE(
		batch
	);
public:
	batch(
		sge::renderer::device::core &,
		sge::renderer::vertex::declaration const &,
		sge::renderer::texture::planar &,
		sge::renderer::vertex::count,
		sge::cegui::clip
	);

	~batch();

	sge::renderer::texture::planar &
	texture() const;

	sge::renderer::vertex::buffer &
	vertex_buffer() const;

	sge::cegui::clip const
	clip() const;
private:
	sge::renderer::texture::planar &texture_;

	sge::renderer::vertex::buffer_scoped_ptr const vertex_buffer_;

	sge::cegui::clip clip_;
};

}
}

#endif

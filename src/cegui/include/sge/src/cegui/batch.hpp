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


#ifndef SGE_SRC_CEGUI_BATCH_HPP_INCLUDED
#define SGE_SRC_CEGUI_BATCH_HPP_INCLUDED

#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/src/cegui/batch_fwd.hpp>
#include <sge/src/cegui/clip.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_wrapper.hpp>


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

	batch(
		batch &&
	);

	batch &
	operator=(
		batch &&
	);

	~batch();

	sge::renderer::texture::planar &
	texture() const;

	sge::renderer::vertex::buffer &
	vertex_buffer() const;

	sge::cegui::clip const
	clip() const;
private:
	typedef
	fcppt::reference_wrapper<
		sge::renderer::texture::planar
	>
	planar_texture_ref;

	planar_texture_ref texture_;

	sge::renderer::vertex::buffer_unique_ptr vertex_buffer_;

	sge::cegui::clip clip_;
};

}
}

#endif

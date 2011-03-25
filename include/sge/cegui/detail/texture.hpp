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


#ifndef SGE_CEGUI_DETAIL_TEXTURE_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_TEXTURE_HPP_INCLUDED

#include <sge/cegui/system_fwd.hpp>
#include <CEGUI/CEGUITexture.h>
#include <CEGUI/CEGUISize.h>
#include <CEGUI/CEGUIString.h>
#include <CEGUI/CEGUIVector.h>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace cegui
{
namespace detail
{
class texture
:
	public CEGUI::Texture
{
FCPPT_NONCOPYABLE(
	texture);
public:
	explicit
	texture(
		system &,
		sge::renderer::texture::capabilities_field const &);

	// We need to handle the empty texture case more than once in the
	// texture target, so this helper function emerged
	bool
	empty() const;

	CEGUI::Size const &
	getSize() const;

	CEGUI::Size const &
	getOriginalDataSize() const;

	CEGUI::Vector2 const &
	getTexelScaling() const;

	void
	resize(
		CEGUI::Size const &);

	void 
	loadFromFile(
		CEGUI::String const &filename,
		CEGUI::String const &resourceGroup);

	void 
	loadFromMemory(
		void const * buffer,
		CEGUI::Size const & buffer_size,
		CEGUI::Texture::PixelFormat pixel_format);

	// This is called by the image_codec to circumvent the
	// loadFromMemory mechanism
	void
	create_from_view(
		sge::image2d::view::const_object const &);

	void 
	saveToMemory(
		void*);

	// The geometry buffer needs this so it can scope the texture
	// correctly.
	sge::renderer::texture::planar_ptr const
	impl();

	~texture();
private:
	system &system_;
	sge::renderer::texture::capabilities_field caps_;
	sge::renderer::texture::planar_ptr texture_;
	// We _have_ to cache this because getSize returns a reference
	CEGUI::Size size_;
	CEGUI::Vector2 texel_scaling_;
};
}
}
}

#endif

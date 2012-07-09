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


#ifndef SGE_SRC_CEGUI_TEXTURE_HPP_INCLUDED
#define SGE_SRC_CEGUI_TEXTURE_HPP_INCLUDED

#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/texture/capabilities_field_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/src/cegui/texture_fwd.hpp>
#include <sge/src/cegui/texture_parameters.hpp>
#include <sge/src/cegui/fwds/sizef_fwd.hpp>
#include <sge/src/cegui/fwds/rectf_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Size.h>
#include <CEGUI/Texture.h>
#include <CEGUI/Vector.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class String;
}

namespace sge
{
namespace cegui
{

class texture
:
	public CEGUI::Texture
{
	FCPPT_NONCOPYABLE(
		texture
	);
public:
	// Constructs a texture that will be loaded later by calling
	// loadFromFile or create_from_view. It won't have a valid size or
	// texture object until then.
	texture(
		sge::cegui::texture_parameters const &,
		CEGUI::String const &name
	);

	// Constructs a texture with a given size, but undefined contents.
	// This texture might be rendered to or it might get data by
	// loadFromMemory.
	texture(
		sge::cegui::texture_parameters const &,
		CEGUI::String const &name,
		CEGUI::Sizef const &,
		sge::renderer::texture::capabilities_field const &
	);

	~texture();

	// The geometry buffer needs this so it can scope the texture
	// correctly.
	sge::renderer::texture::planar &
	impl();

	// This is called by the image_codec to circumvent the
	// loadFromMemory mechanism
	void
	create_from_view(
		sge::image2d::view::const_object const &
	);

	// We need to handle the empty texture case more than once in the
	// texture target, so this helper function emerged
	bool
	empty() const;
private:
	CEGUI::String const &
	getName() const;

	CEGUI::Sizef const &
	getSize() const;

	CEGUI::Sizef const &
	getOriginalDataSize() const;

	CEGUI::Vector2f const &
	getTexelScaling() const;
public:
	void
	loadFromFile(
		CEGUI::String const &filename,
		CEGUI::String const &resourceGroup
	);
private:
	void
	loadFromMemory(
		void const *buffer,
		CEGUI::Sizef const &buffer_size,
		CEGUI::Texture::PixelFormat
	);

	void
	blitFromMemory(
		void *sourceData,
		CEGUI::Rectf const &
	);

	void
	blitToMemory(
		void *
	);

	bool
	isPixelFormatSupported(
		CEGUI::Texture::PixelFormat
	) const;
private:
	sge::cegui::texture_parameters const texture_parameters_;

	CEGUI::String const name_;

	typedef fcppt::optional<
		CEGUI::Sizef
	> optional_sizef;

	// We _have_ to cache this because getSize returns a reference
	sge::cegui::texture::optional_sizef size_;

	typedef fcppt::optional<
		CEGUI::Vector2f
	> optional_vector2f;

	sge::cegui::texture::optional_vector2f texel_scaling_;

	sge::renderer::texture::planar_scoped_ptr texture_;

};

}
}

#endif

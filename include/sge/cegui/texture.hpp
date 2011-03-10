#ifndef SGE_CEGUI_TEXTURE_HPP_INCLUDED
#define SGE_CEGUI_TEXTURE_HPP_INCLUDED

#include "system_fwd.hpp"
#include <sge/class_symbol.hpp>
#include <sge/cegui/symbol.hpp>
#include <CEGUI/CEGUISystem.h>
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
class SGE_CLASS_SYMBOL texture
:
	public CEGUI::Texture
{
FCPPT_NONCOPYABLE(
	texture);
public:
	SGE_CEGUI_SYMBOL explicit
	texture(
		system &,
		sge::renderer::texture::capabilities_field const &);

	// We need to handle the empty texture case more than once in the
	// texture target, so this helper function emerged
	SGE_CEGUI_SYMBOL bool
	empty() const;

	SGE_CEGUI_SYMBOL CEGUI::Size const &
	getSize() const;

	SGE_CEGUI_SYMBOL CEGUI::Size const &
	getOriginalDataSize() const;

	SGE_CEGUI_SYMBOL CEGUI::Vector2 const &
	getTexelScaling() const;

	SGE_CEGUI_SYMBOL void
	resize(
		CEGUI::Size const &);

	SGE_CEGUI_SYMBOL void 
	loadFromFile(
		CEGUI::String const &filename,
		CEGUI::String const &resourceGroup);

	SGE_CEGUI_SYMBOL void 
	loadFromMemory(
		void const * buffer,
		CEGUI::Size const & buffer_size,
		CEGUI::Texture::PixelFormat pixel_format);

	// This is called by the image_codec to circumvent the
	// loadFromMemory mechanism
	SGE_CEGUI_SYMBOL void
	create_from_view(
		sge::image2d::view::const_object const &);

	SGE_CEGUI_SYMBOL void 
	saveToMemory(
		void*);

	// The geometry buffer needs this so it can scope the texture
	// correctly.
	SGE_CEGUI_SYMBOL sge::renderer::texture::planar_ptr const
	impl();

	SGE_CEGUI_SYMBOL ~texture();
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

#endif

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


#ifndef SGE_CEGUI_DETAIL_RENDERER_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_RENDERER_HPP_INCLUDED

#include <sge/cegui/detail/default_target.hpp>
#include <sge/cegui/detail/geometry_buffer.hpp>
#include <sge/cegui/detail/texture_target.hpp>
#include <sge/cegui/detail/texture.hpp>
#include <sge/cegui/system_fwd.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <CEGUI/CEGUIBase.h>
#include <CEGUI/CEGUIRenderer.h>
#include <CEGUI/CEGUIString.h>
#include <CEGUI/CEGUIRenderingRoot.h>
#include <fcppt/noncopyable.hpp> 
#include <fcppt/signal/scoped_connection.hpp> 
#include <fcppt/math/matrix/basic_impl.hpp> 
#include <fcppt/container/array.hpp> 
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>

namespace sge
{
namespace cegui
{
namespace detail
{
class renderer
:
	public CEGUI::Renderer
{
FCPPT_NONCOPYABLE(
	renderer);
public:
	explicit
	renderer(
		system &,
		sge::renderer::device_ptr);

	CEGUI::RenderingRoot &
	getDefaultRenderingRoot();

	CEGUI::GeometryBuffer &
	createGeometryBuffer();

	void 
	destroyGeometryBuffer(
		CEGUI::GeometryBuffer const &);

	void 
	destroyAllGeometryBuffers();

	CEGUI::TextureTarget * 
	createTextureTarget();

	void 
	destroyTextureTarget(
		CEGUI::TextureTarget *);

	void 
	destroyAllTextureTargets();

	CEGUI::Texture & 
	createTexture();

	CEGUI::Texture &
	createTexture(
		CEGUI::String const &filename,
		CEGUI::String const &resourceGroup);

	CEGUI::Texture &
	createTexture(
		CEGUI::Size const &);

	void 
	destroyTexture(
		CEGUI::Texture &);

	void 
	destroyAllTextures();

	void 
	beginRendering();

	void 
	endRendering();

	void 
	setDisplaySize(
		CEGUI::Size const &);

	CEGUI::Size const &
	getDisplaySize() const;

	CEGUI::Vector2 const &
	getDisplayDPI() const;

	CEGUI::uint 
	getMaxTextureSize() const;

	CEGUI::String const & 
	getIdentifierString() const;

	sge::renderer::device_ptr const
	impl() const;

 	~renderer();
private:
	typedef
	boost::ptr_vector<geometry_buffer>
	geometry_buffer_sequence;

	typedef
	boost::ptr_vector<texture_target>
	texture_target_sequence;

	typedef
	boost::ptr_vector<texture>
	texture_sequence;

	system &system_;
	sge::renderer::device_ptr renderer_;
	sge::renderer::vertex_declaration_ptr vertex_declaration_;
	CEGUI::Size display_size_;
	CEGUI::Vector2 display_dpi_;
	CEGUI::String const identifier_;
	default_target default_target_;
	CEGUI::RenderingRoot default_root_;
	geometry_buffer_sequence geometry_buffers_;
	texture_target_sequence texture_targets_;
	texture_sequence textures_;
	fcppt::signal::scoped_connection viewport_change_connection_;

	typedef
	fcppt::container::array<sge::renderer::matrix4,3>
	transform_array;

	transform_array transforms_;
};
}
}
}

#endif

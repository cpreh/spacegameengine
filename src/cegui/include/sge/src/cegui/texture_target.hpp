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


#ifndef SGE_SRC_CEGUI_TEXTURE_TARGET_HPP_INCLUDED
#define SGE_SRC_CEGUI_TEXTURE_TARGET_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/context/scoped_offscreen_target_fwd.hpp>
#include <sge/renderer/target/offscreen_scoped_ptr.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/texture_fwd.hpp>
#include <sge/src/cegui/texture_parameters.hpp>
#include <sge/src/cegui/texture_target_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUIRect.h>
#include <CEGUITextureTarget.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class GeometryBuffer;
class RenderQueue;
class Size;
class Texture;
class Vector2;
}

namespace sge
{
namespace cegui
{

class texture_target
:
	public CEGUI::TextureTarget
{
	FCPPT_NONCOPYABLE(
		texture_target
	);
public:
	texture_target(
		sge::cegui::texture_parameters const &,
		sge::renderer::matrix4 const &projection
	);

	~texture_target();

	void
	render_context(
		sge::cegui::optional_render_context_ref const &
	);
private:
	void
	draw(
		CEGUI::GeometryBuffer const &
	);

	void
	draw(
		CEGUI::RenderQueue const &
	);

	void
	setArea(
		CEGUI::Rect const &
	);

	CEGUI::Rect const &
	getArea() const;

	bool
	isImageryCache() const;

	void
	activate();

	void
	deactivate();

	void
	unprojectPoint(
		CEGUI::GeometryBuffer const & buff,
		CEGUI::Vector2 const &p_in,
		CEGUI::Vector2 & p_out
	) const;

	void
	clear();

	CEGUI::Texture &
	getTexture() const;

	void
	declareRenderSize(
		CEGUI::Size const &
	);

	bool
	isRenderingInverted() const;
private:
	sge::cegui::texture_parameters const texture_parameters_;

	typedef fcppt::scoped_ptr<
		sge::cegui::texture
	> texture_scoped_ptr;

	typedef fcppt::scoped_ptr<
		sge::renderer::context::scoped_offscreen_target
	> offscreen_scoped_ptr;

	sge::renderer::target::offscreen_scoped_ptr const target_;

	sge::cegui::optional_render_context_ref render_context_;

	texture_scoped_ptr texture_;

	offscreen_scoped_ptr scoped_target_;

	CEGUI::Rect area_;

	sge::renderer::matrix4 const default_projection_;
};

}
}

#endif

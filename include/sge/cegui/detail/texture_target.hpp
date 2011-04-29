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


#ifndef SGE_CEGUI_DETAIL_TEXTURE_TARGET_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_TEXTURE_TARGET_HPP_INCLUDED

#include <sge/cegui/system_fwd.hpp>
#include <sge/cegui/detail/texture_fwd.hpp>
#include <CEGUI/CEGUITextureTarget.h>
#include <CEGUI/CEGUISize.h>
#include <CEGUI/CEGUIRect.h>
#include <CEGUI/CEGUIVector.h>
#include <sge/renderer/target_ptr.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace CEGUI
{
class Texture;
class GeometryBuffer;
class RenderQueue;
}

namespace sge
{
namespace cegui
{
namespace detail
{
class texture_target
:
	public CEGUI::TextureTarget
{
FCPPT_NONCOPYABLE(
	texture_target);
public:
	explicit 
	texture_target(
		system &);

	void 
	draw(
		CEGUI::GeometryBuffer const & buffer);

	void 
	draw(
		CEGUI::RenderQueue const & queue);

	void 
	setArea(
		CEGUI::Rect const & area);

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
		CEGUI::Vector2 & p_out) const;

	void 
	clear();

	CEGUI::Texture &
	getTexture() const;

	void 
	declareRenderSize(
		CEGUI::Size const &);

	bool 
	isRenderingInverted() const;

	~texture_target();
private:
	typedef 
	fcppt::scoped_ptr<texture> 
	texture_scoped_ptr;

	system &system_;
	sge::renderer::target_ptr target_;
	texture_scoped_ptr texture_;
	CEGUI::Rect area_;
	sge::renderer::matrix4 temp_projection_;
};
}
}
}

#endif

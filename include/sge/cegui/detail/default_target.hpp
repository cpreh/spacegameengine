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


#ifndef SGE_CEGUI_DETAIL_DEFAULT_TARGET_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_DEFAULT_TARGET_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <CEGUIRenderTarget.h>
#include <CEGUIRect.h>

namespace CEGUI
{
class GeometryBuffer;
class RenderQueue;
class Vector2;
}

namespace sge
{
namespace cegui
{
namespace detail
{
class default_target
:
	public CEGUI::RenderTarget
{
public:
	explicit
	default_target(
		sge::renderer::device &);

	void 
	draw(
		CEGUI::GeometryBuffer const &);

	void 
	draw(
		CEGUI::RenderQueue const &);

	void 
	setArea(
		CEGUI::Rect const &);

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
		CEGUI::GeometryBuffer const &,
		CEGUI::Vector2 const & p_in, 
		CEGUI::Vector2& p_out) const;

	sge::renderer::matrix4 const
	projection() const;
private:
	sge::renderer::device &renderer_;
	mutable CEGUI::Rect viewport_;
};
}
}
}

#endif

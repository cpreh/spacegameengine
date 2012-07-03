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


#ifndef SGE_SRC_CEGUI_DEFAULT_TARGET_HPP_INCLUDED
#define SGE_SRC_CEGUI_DEFAULT_TARGET_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/matrix4_fwd.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/fwds/vector2f_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Rect.h>
#include <CEGUI/RenderTarget.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class GeometryBuffer;
class RenderQueue;
}

namespace sge
{
namespace cegui
{

class default_target
:
	public CEGUI::RenderTarget
{
	FCPPT_NONCOPYABLE(
		default_target
	);
public:
	explicit
	default_target(
		sge::renderer::device &
	);

	~default_target();

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
public:
	void
	setArea(
		CEGUI::Rectf const &
	);
private:
	CEGUI::Rectf const &
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
		CEGUI::Vector2f const &p_in,
		CEGUI::Vector2f &p_out
	) const;
public:
	sge::renderer::matrix4 const
	projection() const;
private:
	sge::renderer::device &renderer_;

	mutable CEGUI::Rectf viewport_;

	sge::cegui::optional_render_context_ref render_context_;
};

}
}

#endif

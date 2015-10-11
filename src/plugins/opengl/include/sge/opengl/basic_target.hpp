/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_BASIC_TARGET_HPP_INCLUDED
#define SGE_OPENGL_BASIC_TARGET_HPP_INCLUDED

#include <sge/opengl/target_base.hpp>
#include <sge/opengl/target_context_fwd.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/box/object_decl.hpp>


namespace sge
{
namespace opengl
{

template<
	typename Base
>
class basic_target
:
	public Base,
	public sge::opengl::target_base
{
	FCPPT_NONCOPYABLE(
		basic_target
	);
protected:
	basic_target(
		sge::opengl::context::device::object &,
		sge::renderer::target::viewport const &
	);
public:
	~basic_target()
	override;
private:
	void
	bind()
	override;

	void
	unbind()
	override;

	void
	viewport(
		sge::renderer::target::viewport const &
	)
	override;

	sge::renderer::target::viewport
	viewport() const
	override;

	void
	scissor_area(
		sge::renderer::target::scissor_area const &
	)
	override;

	sge::renderer::target::scissor_area
	scissor_area() const
	override;

	void
	clear(
		sge::renderer::clear::parameters const &
	)
	override;

	void
	set_viewport();

	void
	set_scissor_area();

	virtual
	sge::renderer::screen_unit
	height() const = 0;

	virtual
	void
	on_bind() = 0;

	virtual
	void
	on_unbind() = 0;

	sge::opengl::target_context &context_;

	bool active_;

	sge::renderer::target::viewport viewport_;

	sge::renderer::target::scissor_area scissor_area_;
};

}
}

#endif

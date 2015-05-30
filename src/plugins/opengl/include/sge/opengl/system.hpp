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


#ifndef SGE_OPENGL_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_SYSTEM_HPP_INCLUDED

#include <sge/opengl/backend/system_fwd.hpp>
#include <sge/opengl/context/system/object.hpp>
#include <sge/opengl/platform/system_fwd.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace opengl
{

class system
:
	public sge::renderer::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	explicit
	system(
		awl::system::object &
	);

	~system()
	override;
private:
	sge::renderer::device::core_unique_ptr
	create_core_renderer(
		sge::renderer::device::parameters const &
	)
	override;

	sge::renderer::device::ffp_unique_ptr
	create_ffp_renderer(
		sge::renderer::device::parameters const &
	)
	override;

	awl::visual::object_unique_ptr
	create_visual(
		sge::renderer::pixel_format::object const &
	)
	override;

	sge::renderer::caps::device_count const
	device_count() const
	override;

	sge::renderer::caps::device const &
	device_caps(
		sge::renderer::device::index
	) const
	override;

	sge::renderer::display_mode::container
	display_modes(
		sge::renderer::device::index
	) const
	override;

	sge::opengl::context::system::object system_context_;

	typedef
	fcppt::unique_ptr<
		sge::opengl::platform::system
	>
	platform_system_unique_ptr;

	platform_system_unique_ptr const platform_system_;

	typedef
	fcppt::unique_ptr<
		sge::opengl::backend::system
	>
	backend_system_unique_ptr;

	backend_system_unique_ptr const backend_system_;

	sge::renderer::caps::device const caps_;
};

}
}

#endif

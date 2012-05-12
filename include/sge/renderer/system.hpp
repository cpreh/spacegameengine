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


#ifndef SGE_RENDERER_SYSTEM_HPP_INCLUDED
#define SGE_RENDERER_SYSTEM_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device_unique_ptr.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/caps/system_field_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**

\brief Creates sge::renderer::device objects and renderable visuals

The core class returned by a renderer plugin. In order to render anything, you
have to create an sge::renderer::device through this class. If you don't have a
renderable window to pass, you can create a renderable visual that can be used
to create one.
*/
class SGE_CLASS_SYMBOL system
{
	FCPPT_NONCOPYABLE(
		system
	);
protected:
	SGE_RENDERER_SYMBOL
	system();
public:
	/**
	 \brief Creates renderer::device objects

	 This function is the starting point if you want to do anything with a
	 renderer plugin.

	 \param params The renderer configuration like resolution and buffers

	 \param adapter A number that tells which device to load. This must be
	 between 0 and the device count minus 1. Every system must have at
	 least one device.

	 \param window The window used for rendering to. This window must
	 satisfy the requirements imposed by \a params

	 \throw sge::renderer::exception if anything goes wrong

	 \return An sge::renderer::device_ptr that may not be null
	*/
	virtual
	sge::renderer::device_unique_ptr
	create_renderer(
		sge::renderer::parameters const &params,
		sge::renderer::adapter adapter,
		awl::window::object &window
	) = 0;

	/**
	 \brief Creates a renderable visual that satisfies the requirements of \a params

	 Creates a renderable visual that satisfies the requirements of \a
	 params and can be used with sge::renderer::system::create_renderer.

	 \param awl_system The awl system that is used to create windows

	 \param params The renderer parameters to satisfy

	 \throw sge::renderer::exception if anything goes wrong

	 \return An awl::visual::object_unique_ptr that may not be null
	*/
	virtual
	awl::visual::object_unique_ptr
	create_visual(
		awl::system::object &awl_system,
		sge::renderer::parameters const &params
	) = 0;

	/**
	\brief Returns the system's capabilities
	*/
	virtual
	sge::renderer::caps::system_field const
	caps() const = 0;

	/**
	\brief Returns the number of devices
	*/
	virtual
	sge::renderer::caps::device_count const
	device_count() const = 0;

	/**
	\brief Queries the capabilities of a device

	Returns the capabilities of the device identified by \a adapter.

	\param adapter The device to query the capabilities for

	\warning The behavior is undefined if adapter is equal to or greater
	than the device count.
	*/
	virtual
	sge::renderer::caps::device const &
	device_caps(
		sge::renderer::adapter adapter
	) const = 0;

	SGE_RENDERER_SYMBOL
	virtual
	~system() = 0;
};

}
}

#endif

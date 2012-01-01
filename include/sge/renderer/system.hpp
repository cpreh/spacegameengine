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
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/window/parameters_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/window/instance_fwd.hpp>
#include <awl/window/instance_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Creates sge::renderer::device objects and renderable windows
 *
 * The core class returned by a renderer plugin. In order to render anything,
 * you have to create an sge::renderer::device through this class. If you don't
 * have a renderable window to pass, you can also create one.
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
	 * \brief Creates renderer::device objects
	 *
	 * This function is the starting point if you want to do anything with
	 * a renderer plugin.
	 *
	 * \param params The renderer configuration like resolution and buffers
	 * \param adapter A number that tells which interface to load, you should currently pass 0
	 * \param window The window used for rendering to. This window must satisfy the requirements imposed by \a params
	 * \throw sge::renderer::exception if anything goes wrong
	 * \return An sge::renderer::device_ptr that may not be null
	*/
	virtual sge::renderer::device_ptr const
	create_renderer(
		sge::renderer::parameters const &params,
		sge::renderer::adapter adapter,
		awl::window::instance &window
	) = 0;

	/**
	 * \brief Creates a renderable window that satisfies the requirements of \a params
	 *
	 * Creates a renderable window that satisfies the requirements of \a
	 * params and can be used with sge::renderer::system::create_renderer.
	 *
	 * \param awl_system The awl system that is used to create windows
	 * \param window_params Basic window parameters like title, dim, size hints, etc.
	 * \param params The renderer parameters to satisfy
	 * \throw sge::renderer::exception if anything goes wrong
	 * \return An awl::window::instance_shared_ptr that may not be null
	*/
	virtual awl::window::instance_shared_ptr const
	create_window(
		awl::system::object &awl_system,
		sge::window::parameters const &window_params,
		sge::renderer::parameters const &params
	) = 0;

	SGE_RENDERER_SYMBOL
	virtual ~system() = 0;
};

}
}

#endif

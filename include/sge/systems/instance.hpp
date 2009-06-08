/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_INSTANCE_HPP_INCLUDED
#define SGE_SYSTEMS_INSTANCE_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/collision/system_fwd.hpp>
#include <sge/window/instance_fwd.hpp>
#include <sge/export.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace plugin
{
class manager;
}

namespace systems
{

class list;

class instance {
	SGE_NONCOPYABLE(instance)
public:
	SGE_SYMBOL explicit instance(
		list const &);
	SGE_SYMBOL ~instance();

	SGE_SYMBOL void reinit(
		list const &);
	
	SGE_SYMBOL plugin::manager &plugin_manager();

	SGE_SYMBOL sge::renderer::system_ptr const renderer_system() const;
	SGE_SYMBOL sge::renderer::device_ptr const renderer() const;

	SGE_SYMBOL input::system_ptr const input_system() const;

	SGE_SYMBOL image::loader_ptr const image_loader() const; // TODO: replace this with an image prober

	SGE_SYMBOL audio::player_ptr const audio_player() const;
	
	SGE_SYMBOL collision::system_ptr const collision_system() const;

	SGE_SYMBOL font::system_ptr const font_system() const;

	SGE_SYMBOL sge::window::instance_ptr const window() const;

	class impl;
private:
	sge::scoped_ptr<impl> impl_;
};

}
}

#endif

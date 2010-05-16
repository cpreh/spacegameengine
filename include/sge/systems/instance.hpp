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

#include <sge/systems/list_fwd.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/system_ptr.hpp>
#include <sge/font/system_ptr.hpp>
#include <sge/input/system_ptr.hpp>
#include <sge/image/multi_loader_fwd.hpp>
#include <sge/audio/player_ptr.hpp>
#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/collision/system_ptr.hpp>
#include <sge/window/instance_ptr.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/symbol.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace systems
{

class instance
{
	FCPPT_NONCOPYABLE(instance)
public:
	SGE_SYMBOL explicit instance(
		list const &
	);

	SGE_SYMBOL ~instance();

	SGE_SYMBOL void
	reinit(
		list const &
	);

	SGE_SYMBOL plugin::manager &
	plugin_manager();

	SGE_SYMBOL sge::renderer::system_ptr const
	renderer_system() const;

	SGE_SYMBOL sge::renderer::device_ptr const
	renderer() const;

	SGE_SYMBOL input::system_ptr const
	input_system() const;

	SGE_SYMBOL sge::image::multi_loader const &
	image_loader() const;

	SGE_SYMBOL sge::audio::multi_loader const &
	audio_loader() const;

	SGE_SYMBOL sge::audio::player_ptr const
	audio_player() const;

	SGE_SYMBOL collision::system_ptr const
	collision_system() const;

	SGE_SYMBOL font::system_ptr const
	font_system() const;

	SGE_SYMBOL sge::window::instance_ptr const
	window() const;

	class impl;
private:
	fcppt::scoped_ptr<impl> impl_;
};

}
}

#endif

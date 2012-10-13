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


#ifndef SGE_SYSTEMS_INSTANCE_DECL_HPP_INCLUDED
#define SGE_SYSTEMS_INSTANCE_DECL_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/instance_fwd.hpp>
#include <sge/systems/list_fwd.hpp>
#include <sge/systems/detail/assert_dependencies.hpp>
#include <sge/systems/detail/instance.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/static_assert_statement.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

template<
	typename Choices
>
class instance
{
	FCPPT_NONCOPYABLE(
		instance
	);

	FCPPT_STATIC_ASSERT_STATEMENT(
		boost::mpl::is_sequence<
			Choices
		>::value
	);

	FCPPT_STATIC_ASSERT_STATEMENT(
		sge::systems::detail::assert_dependencies<
			Choices
		>::value
	);
public:
	template<
		typename Inits
	>
	explicit
	instance(
		sge::systems::list<
			Inits
		> const &
	);

	~instance();

	sge::plugin::manager &
	plugin_manager();

	sge::renderer::system &
	renderer_system() const;

	sge::renderer::device::ffp &
	renderer_ffp() const;

	sge::renderer::device::core &
	renderer_core() const;

	sge::input::system &
	input_system() const;

	sge::input::processor &
	input_processor() const;

	sge::input::cursor::object &
	cursor_demuxer() const;

	sge::input::keyboard::device &
	keyboard_collector() const;

	sge::input::mouse::device &
	mouse_collector() const;

	sge::image2d::system &
	image_system() const;

	sge::audio::loader &
	audio_loader() const;

	sge::audio::player &
	audio_player() const;

	sge::charconv::system &
	charconv_system() const;

	sge::font::system &
	font_system() const;

	sge::window::system &
	window_system() const;

	sge::window::object &
	window() const;

	sge::viewport::manager &
	viewport_manager() const;
private:
	sge::systems::detail::instance instance_;
};

}
}

#endif

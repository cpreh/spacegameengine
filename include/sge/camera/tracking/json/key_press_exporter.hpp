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


#ifndef SGE_CAMERA_TRACKING_JSON_KEY_PRESS_EXPORTER_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_JSON_KEY_PRESS_EXPORTER_HPP_INCLUDED

#include <sge/camera/base_fwd.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/tracking/keyframe_sequence.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/signal/connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace camera
{
namespace tracking
{
namespace json
{
class key_press_exporter
{
FCPPT_NONCOPYABLE(
	key_press_exporter);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::input::key::code,
		keyframe_keypress);

	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::input::key::code,
		export_keypress);

	SGE_CAMERA_DETAIL_SYMBOL
	key_press_exporter(
		sge::camera::base const &,
		boost::filesystem::path const &,
		sge::camera::update_duration const &,
		sge::input::keyboard::device &,
		keyframe_keypress const &,
		export_keypress const &);

	SGE_CAMERA_DETAIL_SYMBOL
	~key_press_exporter();
private:
	sge::camera::base const &camera_;
	boost::filesystem::path const target_path_;
	sge::camera::update_duration const duration_;
	keyframe_keypress const keyframe_keypress_;
	export_keypress const export_keypress_;
	fcppt::signal::scoped_connection const key_press_connection_;
	sge::camera::tracking::keyframe_sequence keyframes_;

	void
	key_callback(
		sge::input::keyboard::key_event const &);
};
}
}
}
}

#endif

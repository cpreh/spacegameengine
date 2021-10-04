//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_TRACKING_JSON_KEY_PRESS_EXPORTER_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_JSON_KEY_PRESS_EXPORTER_HPP_INCLUDED

#include <sge/camera/base_fwd.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/tracking/keyframe_sequence.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/input/keyboard/event/key_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge::camera::tracking::json
{

class key_press_exporter
{
	FCPPT_NONMOVABLE(
		key_press_exporter
	);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::input::key::code,
		keyframe_keypress
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::input::key::code,
		export_keypress
	);

	SGE_CAMERA_DETAIL_SYMBOL
	key_press_exporter(
		fcppt::log::context_reference,
		sge::camera::base const &,
		std::filesystem::path &&,
		sge::camera::update_duration const &,
		keyframe_keypress const &,
		export_keypress const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	~key_press_exporter();

	SGE_CAMERA_DETAIL_SYMBOL
	void
	process_event(
		sge::input::event_base const &
	);
private:
	fcppt::log::object log_;

	sge::camera::base const &camera_;

	std::filesystem::path const target_path_;

	sge::camera::update_duration const duration_;

	keyframe_keypress const keyframe_keypress_;

	export_keypress const export_keypress_;

	sge::camera::tracking::keyframe_sequence keyframes_;

	void
	key_event(
		sge::input::keyboard::event::key const &
	);
};

}

#endif

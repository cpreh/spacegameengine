//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_INSTANCE_DECL_HPP_INCLUDED
#define SGE_SYSTEMS_INSTANCE_DECL_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/renderer/core_fwd.hpp>
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
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

template<
	typename... Choices
>
class instance
{
	FCPPT_NONCOPYABLE(
		instance
	);

	typedef
	metal::list<
		Choices...
	>
	choices_list;

	static_assert(
		sge::systems::detail::assert_dependencies<
			choices_list
		>::value,
		"systems::instance dependencies are not met"
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

	fcppt::log::context_reference
	log_context() const;

	sge::plugin::manager &
	plugin_manager();

	sge::renderer::core &
	renderer_core() const;

	sge::renderer::system &
	renderer_system() const;

	sge::renderer::device::ffp &
	renderer_device_ffp() const;

	sge::renderer::device::core &
	renderer_device_core() const;

	sge::input::system &
	input_system() const;

	sge::input::processor &
	input_processor() const;

	sge::image2d::system &
	image_system() const;

	sge::audio::loader &
	audio_loader() const;

	sge::audio::player &
	audio_player() const;

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

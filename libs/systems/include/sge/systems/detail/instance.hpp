//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_INSTANCE_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_INSTANCE_HPP_INCLUDED

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
#include <sge/systems/detail/instance_impl_fwd.hpp>
#include <sge/systems/detail/list_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sge::systems::detail
{

class instance
{
	FCPPT_NONMOVABLE(
		instance
	);
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	instance(
		sge::systems::detail::list const &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	~instance();

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	fcppt::log::context_reference
	log_context() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::plugin::manager &
	plugin_manager();

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::renderer::core &
	renderer_core() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::renderer::system &
	renderer_system() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::renderer::device::ffp &
	renderer_device_ffp() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::renderer::device::core &
	renderer_device_core() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::input::system &
	input_system() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::input::processor &
	input_processor() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::image2d::system &
	image_system() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::audio::loader &
	audio_loader() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::audio::player &
	audio_player() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::font::system &
	font_system() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::window::system &
	window_system() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::window::object &
	window() const;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::viewport::manager &
	viewport_manager() const;
private:
	using
	impl_ptr
	=
	fcppt::unique_ptr<
		sge::systems::detail::instance_impl
	>;

	impl_ptr const impl_;
};

}

#endif

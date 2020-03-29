//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_RENDERER_SYSTEM_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_RENDERER_SYSTEM_HPP_INCLUDED

#include <sge/parse/ini/optional_start_fwd.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/plugin/collection_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <sge/systems/impl/renderer/plugin_core_pair.hpp>
#include <sge/systems/impl/renderer/system_fwd.hpp>
#include <sge/systems/impl/window/system_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace renderer
{

class system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system(
		fcppt::log::context_reference,
		sge::renderer::plugin::collection const &,
		sge::systems::detail::renderer const &,
		sge::parse::ini::optional_start const &,
		sge::systems::impl::window::system const &
	);

	~system();

	awl::visual::object_unique_ptr
	create_visual();

	sge::renderer::core &
	core() const;

	sge::renderer::system &
	get() const;
private:
	sge::renderer::pixel_format::object const pixel_format_;

	sge::systems::impl::renderer::plugin_core_pair const plugin_core_pair_;

	sge::renderer::system_unique_ptr const renderer_system_;
};

}
}
}
}

#endif

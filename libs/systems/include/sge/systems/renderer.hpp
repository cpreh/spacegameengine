//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_RENDERER_HPP_INCLUDED
#define SGE_SYSTEMS_RENDERER_HPP_INCLUDED

#include <sge/plugin/name.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <sge/viewport/optional_resize_callback.hpp>


namespace sge
{
namespace systems
{

class renderer
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	renderer(
		sge::renderer::pixel_format::object const &,
		sge::renderer::display_mode::parameters const &,
		sge::viewport::optional_resize_callback const &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::renderer &
	caps(
		sge::renderer::caps::system_field const &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::renderer &
	name(
		sge::plugin::name const &
	);

	sge::renderer::pixel_format::object const &
	pixel_format() const;

	sge::renderer::display_mode::parameters const &
	display_mode() const;

	sge::viewport::optional_resize_callback const &
	resize_callback() const;

	sge::renderer::caps::system_field const &
	caps() const;

	sge::systems::optional_name const &
	name() const;
private:
	sge::renderer::pixel_format::object pixel_format_;

	sge::renderer::display_mode::parameters display_mode_;

	sge::viewport::optional_resize_callback resize_callback_;

	sge::renderer::caps::system_field caps_;

	sge::systems::optional_name name_;
};

}
}

#endif

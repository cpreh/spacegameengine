/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SYSTEMS_RENDERER_HPP_INCLUDED
#define SGE_SYSTEMS_RENDERER_HPP_INCLUDED

#include <sge/plugin/name.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <sge/viewport/resize_callback.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace systems
{

class renderer
{
	FCPPT_NONASSIGNABLE(
		renderer
	);
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	renderer(
		sge::renderer::pixel_format::object const &,
		sge::renderer::display_mode::parameters const &,
		sge::viewport::resize_callback const &
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

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::renderer &
	device_index(
		sge::renderer::device::index
	);

	sge::renderer::pixel_format::object const &
	pixel_format() const;

	sge::renderer::display_mode::parameters const &
	display_mode() const;

	sge::viewport::resize_callback const &
	resize_callback() const;

	sge::renderer::caps::system_field const &
	caps() const;

	sge::systems::optional_name const &
	name() const;

	sge::renderer::device::index const
	device_index() const;
private:
	sge::renderer::pixel_format::object const pixel_format_;

	sge::renderer::display_mode::parameters const display_mode_;

	sge::viewport::resize_callback const resize_callback_;

	sge::renderer::caps::system_field caps_;

	sge::systems::optional_name name_;

	sge::renderer::device::index device_index_;
};

}
}

#endif

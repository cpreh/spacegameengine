/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_WINDOW_HPP_INCLUDED
#define SGE_SYSTEMS_WINDOW_HPP_INCLUDED

#include <sge/window/simple_parameters.hpp>
#include <sge/systems/symbol.hpp>
#include <sge/systems/wrapped_window.hpp>
#include <awl/mainloop/io_service_ptr.hpp>
#include <awl/window/event/processor_ptr.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace systems
{

class window
{
public:
	SGE_SYSTEMS_SYMBOL
	explicit window(
		sge::window::simple_parameters const &
	);

	SGE_SYSTEMS_SYMBOL
	explicit window(
		sge::systems::wrapped_window const &
	);

	SGE_SYSTEMS_SYMBOL
	window &
	event_processor(
		awl::window::event::processor_ptr
	);

	SGE_SYSTEMS_SYMBOL
	window &
	io_service(
		awl::mainloop::io_service_ptr
	);

	typedef fcppt::variant::object<
		boost::mpl::vector2<
			sge::window::simple_parameters,
			sge::systems::wrapped_window
		>
	> parameter_variant;

	SGE_SYSTEMS_SYMBOL
	parameter_variant const &
	parameter() const;

	SGE_SYSTEMS_SYMBOL
	awl::window::event::processor_ptr const
	window_event_processor() const;

	SGE_SYSTEMS_SYMBOL
	awl::mainloop::io_service_ptr const
	io_service() const;
private:
	parameter_variant parameter_;

	awl::window::event::processor_ptr window_processor_;

	awl::mainloop::io_service_ptr io_service_;
};

}
}

#endif

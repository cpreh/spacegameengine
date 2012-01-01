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


#ifndef SGE_SYSTEMS_WINDOW_HPP_INCLUDED
#define SGE_SYSTEMS_WINDOW_HPP_INCLUDED

#include <sge/systems/symbol.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/wrapped_window.hpp>
#include <sge/window/parameters.hpp>
#include <awl/mainloop/io_service_fwd.hpp>
#include <awl/mainloop/optional_io_service_ref.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

class window
{
	FCPPT_NONASSIGNABLE(
		window
	);
public:
	typedef fcppt::variant::object<
		boost::mpl::vector2<
			sge::window::parameters,
			sge::systems::wrapped_window
		>
	> parameter_variant;

	SGE_SYSTEMS_SYMBOL
	explicit window(
		parameter_variant const &
	);

	SGE_SYSTEMS_SYMBOL
	window &
	io_service(
		awl::mainloop::io_service &
	);

	SGE_SYSTEMS_SYMBOL
	window &
	dont_show();

	SGE_SYSTEMS_SYMBOL
	parameter_variant const &
	parameter() const;

	SGE_SYSTEMS_SYMBOL
	awl::mainloop::optional_io_service_ref const
	io_service() const;

	SGE_SYSTEMS_SYMBOL
	bool
	show() const;
private:
	parameter_variant const parameter_;

	awl::mainloop::optional_io_service_ref io_service_;

	bool show_;
};

}
}

#endif

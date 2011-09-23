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


#ifndef SGE_X11INPUT_DEVICE_MANAGER_CONFIG_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_MANAGER_CONFIG_HPP_INCLUDED

#include "id.hpp"
#include "manager_config_base.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/signal/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace x11input
{
namespace device
{

template<
	typename X11ObjectPtr,
	typename ObjectPtr
>
class manager_config
:
	public device::manager_config_base
{
	FCPPT_NONCOPYABLE(
		manager_config
	);
public:
	typedef std::vector<
		X11ObjectPtr
	> object_vector;

	typedef fcppt::signal::object<
		void (ObjectPtr)
	> signal;

	typedef fcppt::function::object<
		X11ObjectPtr const (
			device::id
		)
	> create_function;

	manager_config(
		object_vector &,
		signal &discover,
		signal &remove,
		create_function const &
	);

	~manager_config();

	void
	initial(
		x11input::device::id
	);

	void
	add(
		x11input::device::id
	);

	void
	remove(
		x11input::device::id
	);
private:
	object_vector &objects_;

	signal &discover_;

	signal &remove_;

	create_function const create_;
};

}
}
}

#endif

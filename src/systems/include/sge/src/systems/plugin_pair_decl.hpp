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


#ifndef SGE_SRC_SYSTEMS_PLUGIN_PAIR_DECL_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_PLUGIN_PAIR_DECL_HPP_INCLUDED

#include <sge/plugin/object_shared_ptr.hpp>
#include <sge/src/systems/plugin_pair_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/shared_ptr_impl.hpp>


namespace sge
{
namespace systems
{

template<
	typename System
>
class plugin_pair
{
	FCPPT_NONASSIGNABLE(
		plugin_pair
	);
public:
	typedef typename sge::plugin::object_shared_ptr<
		System
	>::type plugin_shared_ptr;

	typedef fcppt::shared_ptr<
		System
	> system_shared_ptr;

	plugin_pair(
		plugin_shared_ptr,
		system_shared_ptr
	);

	System &
	system() const;
private:
	plugin_shared_ptr const plugin_;

	system_shared_ptr const system_;
};

}
}

#endif

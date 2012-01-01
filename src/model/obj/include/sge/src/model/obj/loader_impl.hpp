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


#ifndef SGE_SRC_MODEL_OBJ_LOADER_IMPL_HPP_INCLUDED
#define SGE_SRC_MODEL_OBJ_LOADER_IMPL_HPP_INCLUDED

#include <sge/model/obj/instance_ptr.hpp>
#include <sge/model/obj/loader.hpp>
#include <sge/src/model/obj/tokens.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/filesystem/path.hpp>


namespace sge
{
namespace model
{
namespace obj
{

class loader_impl
:
	public obj::loader
{
	FCPPT_NONCOPYABLE(
		loader_impl
	);
public:
	loader_impl();

	~loader_impl();
private:
	obj::instance_ptr const
	load(
		fcppt::filesystem::path const &
	);

	obj::tokens tokens_;
};

}
}
}

#endif

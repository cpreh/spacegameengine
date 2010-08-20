/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MODEL_LOADER_HPP_INCLUDED
#define SGE_MODEL_LOADER_HPP_INCLUDED

#include <sge/model/loader_fwd.hpp>
#include <sge/model/object_ptr.hpp>
#include <sge/model/istream.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/filesystem/path.hpp>

namespace sge
{
namespace model
{

class SGE_CLASS_SYMBOL loader
{
	FCPPT_NONCOPYABLE(loader)
protected:
	SGE_SYMBOL loader();
public:
	virtual object_ptr const
	load(
		istream &
	) = 0;

	virtual object_ptr const
	load(
		fcppt::filesystem::path const &) = 0;

	SGE_SYMBOL virtual ~loader();
};

}
}

#endif

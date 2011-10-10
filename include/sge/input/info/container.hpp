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


#ifndef SGE_INPUT_INFO_CONTAINER_HPP_INCLUDED
#define SGE_INPUT_INFO_CONTAINER_HPP_INCLUDED

#include <sge/input/info/container_fwd.hpp>
#include <sge/input/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace input
{
namespace info
{

template<
	typename Id,
	typename Obj
>
class container
{
public:
	typedef Id id;

	typedef Obj object;

	typedef std::vector<
		Obj
	> vector;

	SGE_INPUT_SYMBOL
	explicit container(
		vector const &
	);

	SGE_INPUT_SYMBOL
	Obj const &
	operator[](
		Id const &
	) const;

	SGE_INPUT_SYMBOL
	Id const
	size() const;

	SGE_INPUT_SYMBOL
	vector const &
	get() const;
private:
	vector vector_;
};

}
}
}

#endif

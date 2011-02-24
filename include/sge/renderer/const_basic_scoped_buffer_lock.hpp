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


#ifndef SGE_RENDERER_CONST_BASIC_SCOPED_BUFFER_LOCK_HPP_INCLUDED
#define SGE_RENDERER_CONST_BASIC_SCOPED_BUFFER_LOCK_HPP_INCLUDED

#include <sge/renderer/npos.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace renderer
{

template<
	typename Ptr,
	typename View
>
class const_basic_scoped_buffer_lock
{
	FCPPT_NONCOPYABLE(
		const_basic_scoped_buffer_lock
	);
public:
	SGE_SYMBOL explicit const_basic_scoped_buffer_lock(
		Ptr,
		size_type first = 0,
		size_type count = renderer::npos()
	);

	SGE_SYMBOL View const
	value() const;

	SGE_SYMBOL ~const_basic_scoped_buffer_lock();
private:
	Ptr const ptr_;

	View const view_;
};

}
}

#endif

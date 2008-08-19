/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_LOCK_HPP_INCLUDED

#include "scoped_lock_wrapper.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace renderer
{

template<typename T, typename Value>
class scoped_lock : boost::noncopyable {
public:
	typedef scoped_lock_wrapper<
		T,
		Value
	> wrapper;

	explicit scoped_lock(
		wrapper const& w);

	void release();

	Value const value() const;

	~scoped_lock();
private:
	void unlock();

	wrapper w;
};

/*template<typename Ret, typename T>
const typename scoped_lock<T, Ret>::wrapper
make_scoped_lock(
	T const t,
	lock_flag_t const flags)
{
	return typename scoped_lock<T, Ret>::wrapper(
		t,
		t->lock(flags));
}*/

}
}

#endif

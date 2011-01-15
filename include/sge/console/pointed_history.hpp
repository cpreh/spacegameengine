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


#ifndef SGE_CONSOLE_POINTED_HISTORY_HPP_INCLUDED
#define SGE_CONSOLE_POINTED_HISTORY_HPP_INCLUDED

#include <fcppt/assert.hpp>
#include <boost/circular_buffer.hpp>

namespace sge
{
namespace console
{
template<typename T>
class pointed_history
{
public:
	typedef
	T
	value_type;
	
	typedef 
	boost::circular_buffer<value_type> 
	container;
	
	typedef typename
	container::size_type
	size_type;
	
	typedef typename
	container::iterator
	iterator;
	
	typedef typename
	container::const_iterator
	const_iterator;
	
	pointed_history(
		size_type const _limit)
	:
		container_(
			_limit),
		point_(
			static_cast<size_type>(
				0))
	{
		FCPPT_ASSERT(_limit);
	}
	
	void
	push_front(
		T const &_t)
	{
		container_.push_front(
			_t);
		if (point_ != static_cast<size_type>(0))
			++point_;
	}
	
	void
	up()
	{
		if (point_ != static_cast<size_type>(container_.size()-1))
			point_++;
	}
	
	void
	down()
	{
		if (point_ != static_cast<size_type>(0))
			point_--;
	}
	
	bool empty() const
	{
		return 
			container_.empty();
	}
	
	iterator const point()
	{
		return 
			boost::next(
				container_.begin(),
				point_);
	}
	
	const_iterator const point() const
	{
		return 
			boost::next(
				container_.begin(),
				point_);
	}
	
	iterator const end()
	{
		return 
			container_.end();
	}
	
	const_iterator const end() const
	{
		return 
			container_.end();
	}
private:
	container container_;
	size_type point_;
};
}
}

#endif

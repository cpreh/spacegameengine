/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/console/detail/history.hpp>
#include <sge/input/modifier/states.hpp>
#include <sge/input/key_type.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/math/almost_zero.hpp>
#include <sge/assert.hpp>
#include <boost/next_prior.hpp>

sge::console::detail::history::history()
:
	items_(),
	pos_(items_.begin())
{
}

sge::console::detail::history::iterator_pair const 
	sge::console::detail::history::lines_inside(
	rect const &r,
	unit const height) const
{
	SGE_ASSERT(!math::almost_zero(height));
	
	// draw history
	unit const total_lines = static_cast<unit>(r.h()/height);

	// go from pos_ to min(pos_+total_lines,end)
	const_iterator it = pos_;
	for (unit i = static_cast<unit>(0); 
	     i < total_lines && it != items_.end(); 
			 ++i)
		++it;

	return boost::make_iterator_range(
		const_iterator(pos_),
		const_iterator(it));
}

void sge::console::detail::history::up()
{
	if (pos_ == --items_.end())
		return;
	pos_ = boost::next(pos_);
}

void sge::console::detail::history::down()
{
	if (pos_ == items_.begin())
		return;
	pos_ = boost::prior(pos_);
}

sge::string const sge::console::detail::history::current() const
{
	return *pos_;
}

void sge::console::detail::history::push_front(string const &s)
{
	iterator::difference_type const d = 
		std::distance(
			items_.begin(),
			pos_);
	items_.push_front(s);
	pos_ = boost::next(items_.begin(),d);
}

void sge::console::detail::history::push_back(string const &s)
{
	iterator::difference_type const d = 
		std::distance(
			items_.begin(),
			pos_);
	items_.push_back(s);
	pos_ = boost::next(items_.begin(),d);
}

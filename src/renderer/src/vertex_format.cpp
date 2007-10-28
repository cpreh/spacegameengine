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


#include <algorithm>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include "../vertex_format.hpp"

sge::vertex_element::vertex_element(const vertex_usage::type _usage, const vertex_size _count)
 : _usage(_usage),
   _count(_count),
  _size(vertex_element_size[_usage])
{}

sge::vertex_usage::type sge::vertex_element::usage() const
{
	return _usage;
}

sge::vertex_size sge::vertex_element::size() const
{
	return _size;
}

sge::vertex_size sge::vertex_element::count() const
{
	return _count;
}

sge::vertex_size sge::vertex_element::stride() const
{
	return size()*count();
}


sge::vertex_format::vertex_format()
: _stride(0)
{}

const sge::vertex_format::usage_list& sge::vertex_format::elements() const
{
	return ulist;
}

sge::vertex_size sge::vertex_format::stride() const
{
	return _stride;
}

sge::vertex_format& sge::vertex_format::add(const vertex_usage::type u, const vertex_size count)
{
	oi[u] = _stride;
	ulist.push_back(vertex_element(u,count));
	_stride += vertex_element_size[u] * count;
	return *this;
}

const sge::offset_info& sge::vertex_format::offsets() const
{
	return oi;
}

bool sge::vertex_format::uses(const vertex_usage::type e) const
{
	return std::find_if(ulist.begin(),ulist.end(),boost::lambda::bind(&vertex_element::usage,boost::lambda::_1) == e) != ulist.end();
}

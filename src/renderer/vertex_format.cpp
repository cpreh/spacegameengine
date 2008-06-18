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


#include <sge/renderer/vertex_format.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <algorithm>

sge::renderer::vertex_element::vertex_element(
	const vertex_usage::type usage_,
	const vertex_size count_)
 : usage_(usage_),
   count_(count_),
  size_(vertex_element_size[usage_])
{}

sge::renderer::vertex_usage::type
sge::renderer::vertex_element::usage() const
{
	return usage_;
}

sge::renderer::vertex_size
sge::renderer::vertex_element::size() const
{
	return size_;
}

sge::renderer::vertex_size
sge::renderer::vertex_element::count() const
{
	return count_;
}

sge::renderer::vertex_size
sge::renderer::vertex_element::stride() const
{
	return size() * count();
}


sge::renderer::vertex_format::vertex_format()
: stride_(0)
{}

sge::renderer::vertex_format::usage_list const &
sge::renderer::vertex_format::elements() const
{
	return ulist;
}

sge::renderer::vertex_size
sge::renderer::vertex_format::stride() const
{
	return stride_;
}

sge::renderer::vertex_format &
sge::renderer::vertex_format::add(
	const vertex_usage::type u,
	const vertex_size count)
{
	oi[u] = stride_;
	ulist.push_back(vertex_element(u, count));
	stride_ += vertex_element_size[u] * count;
	return *this;
}

sge::renderer::offset_info const &
sge::renderer::vertex_format::offsets() const
{
	return oi;
}

bool sge::renderer::vertex_format::uses(
	const vertex_usage::type e) const
{
	return std::find_if(
		ulist.begin(),
		ulist.end(),
		boost::lambda::bind(
			&vertex_element::usage,
			boost::lambda::_1) == e)
		!= ulist.end();
}

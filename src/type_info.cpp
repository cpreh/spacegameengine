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


#include <sge/type_info.hpp>
#include <sge/assert.hpp>

sge::type_info::type_info(const std::type_info& ti)
: info_(&ti)
{ 
	SGE_ASSERT(info_); 
}

bool sge::type_info::before(const type_info& rhs) const
{
	SGE_ASSERT(info_);
	return info_->before(*rhs.info_);
}

const std::type_info& sge::type_info::get() const
{
	SGE_ASSERT(info_);
	return *info_;
}

const char* sge::type_info::name() const
{
	SGE_ASSERT(info_);
	return info_->name();
}

bool sge::operator==(const type_info& lhs, const type_info& rhs)
{
	return lhs.get() == rhs.get();
}

bool sge::operator<(const type_info& lhs, const type_info& rhs)
{
	return lhs.before(rhs);
}

bool sge::operator!=(const type_info& lhs, const type_info& rhs)
{
	return !(lhs == rhs);
}

bool sge::operator>(const type_info& lhs, const type_info& rhs)
{
	return rhs < lhs;
}

bool sge::operator<=(const type_info& lhs, const type_info& rhs)
{
	return !(lhs > rhs);
}

bool sge::operator>=(const type_info& lhs, const type_info& rhs)
{
	return !(lhs < rhs);
}

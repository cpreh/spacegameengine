/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_MODEL_MD3_IMPL_TAG_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_TAG_HPP_INCLUDED

#include <sge/model/md3/string.hpp>
#include <sge/model/md3/impl/axis_array.hpp>
#include <sge/model/md3/impl/vec3.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace md3
{
namespace impl
{

class tag
{
public:
	explicit
	tag(
		std::istream &
	);

	sge::model::md3::string const &
	name() const;

	sge::model::md3::impl::vec3 const &
	origin() const;

	sge::model::md3::impl::axis_array const &
	axis() const;
private:
	sge::model::md3::string name_;

	sge::model::md3::impl::vec3 origin_;

	sge::model::md3::impl::axis_array axis_;
};

}
}
}
}

#endif

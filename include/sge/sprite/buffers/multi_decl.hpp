/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_BUFFERS_MULTI_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_MULTI_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/multi_fwd.hpp>
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/slice_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace buffers
{

template<
	typename Choices
>
class multi
{
	FCPPT_NONCOPYABLE(
		multi
	);
public:
	typedef Choices choices;

	multi(
		sge::sprite::buffers::parameters const &,
		sge::sprite::buffers::option
	);

	~multi();

	typedef sge::sprite::buffers::slice<
		Choices
	> slice_type;

	slice_type &
	allocate(
		sge::sprite::count
	);

	sge::sprite::buffers::parameters const &
	parameters() const;
private:
	typedef typename sge::sprite::buffers::object<
		Choices
	>::type buffer_object;

	sge::sprite::buffers::parameters const parameters_;

	sge::sprite::buffers::option const buffers_option_;

	typedef std::vector<
		buffer_object
	> buffer_object_vector;

	typedef boost::ptr_vector<
		slice_type
	> slice_vector;

	buffer_object_vector buffer_objects_;

	slice_vector slices_;
};

}
}
}

#endif

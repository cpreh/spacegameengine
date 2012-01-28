/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_BUFFERS_SINGLE_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_SINGLE_DECL_HPP_INCLUDED

#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/single_fwd.hpp>
#include <sge/sprite/buffers/slice_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_decl.hpp>


namespace sge
{
namespace sprite
{
namespace buffers
{

template<
	typename Choices
>
class single
{
	FCPPT_NONCOPYABLE(
		single
	);
public:
	typedef Choices choices;

	single(
		sge::sprite::buffers::parameters const &,
		sge::sprite::buffers::option::type
	);

	~single();

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
	>::type buffers_object;

	sge::sprite::buffers::parameters const parameters_;

	sge::sprite::buffers::option::type const buffers_option_;

	buffers_object buffers_object_;

	typedef fcppt::scoped_ptr<
		slice_type
	> optional_slice;

	optional_slice slice_;
};

}
}
}

#endif

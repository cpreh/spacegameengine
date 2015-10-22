/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_TEXTURE_CONST_BASIC_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CONST_BASIC_SCOPED_LOCK_HPP_INCLUDED

#include <sge/renderer/buffer/const_scoped_lock.hpp>
#include <sge/renderer/buffer/readable.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

template<
	typename Texture
>
class const_basic_scoped_lock
{
	FCPPT_NONCOPYABLE(
		const_basic_scoped_lock
	);
public:
	typedef
	typename
	Texture::const_buffer
	buffer;

	typedef
	typename
	buffer::lock_area
	lock_area;

	typedef
	typename
	buffer::const_view
	const_view;

	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	const_basic_scoped_lock(
		Texture const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	const_basic_scoped_lock(
		Texture const &,
		lock_area const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	const_view
	value() const;

	SGE_RENDERER_DETAIL_SYMBOL
	~const_basic_scoped_lock();
private:
	typedef
	sge::renderer::buffer::const_scoped_lock<
		buffer
	>
	buffer_lock;

	buffer_lock const lock_;
};

}
}
}

#endif

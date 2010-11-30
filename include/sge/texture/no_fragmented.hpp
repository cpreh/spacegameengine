/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_TEXTURE_NO_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_NO_FRAGMENTED_HPP_INCLUDED

#include <sge/texture/fragmented.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/symbol.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/filter/texture.hpp>
#include <sge/image/color/format.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace texture
{

class SGE_CLASS_SYMBOL no_fragmented
:
	public fragmented
{
	FCPPT_NONCOPYABLE(
		no_fragmented
	)
public:
	SGE_TEXTURE_SYMBOL no_fragmented(
		renderer::device_ptr,
		image::color::format::type,
		renderer::filter::texture const &
	);
private:
	part_ptr const
	consume_fragment(
		renderer::dim2 const &
	);

	void
	on_return_fragment(
		part const &
	);

	renderer::texture_ptr const
	texture() const;

	bool repeatable() const;

	free_type
	free_value() const;

	bool
	empty() const;

	renderer::device_ptr const rend_;

	image::color::format::type const format_;

	renderer::filter::texture const filter_;

	renderer::texture_ptr tex_;
};

}
}

#endif


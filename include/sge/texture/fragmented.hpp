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


#ifndef SGE_TEXTURE_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_FRAGMENTED_HPP_INCLUDED

#include <sge/texture/fragmented_fwd.hpp>
#include <sge/texture/manager_fwd.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/free_type.hpp>
#include <sge/texture/symbol.hpp>
#include <sge/texture/detail/optional_container_position.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_impl.hpp>

namespace sge
{
namespace texture
{

class SGE_CLASS_SYMBOL fragmented
{
	FCPPT_NONCOPYABLE(
		fragmented
	);
protected:
	SGE_TEXTURE_SYMBOL fragmented();
public:
	SGE_TEXTURE_SYMBOL virtual ~fragmented();

	virtual texture::part_ptr const
	consume_fragment(
		renderer::dim2 const &
	) = 0;

	SGE_TEXTURE_SYMBOL void
	return_fragment(
		part const &
	);

	virtual renderer::texture::planar &
	texture() = 0;

	virtual renderer::texture::planar const &
	texture() const = 0;

	virtual bool
	repeatable() const = 0;

	virtual free_type
	free_value() const = 0;

	virtual bool
	empty() const = 0;

	SGE_TEXTURE_SYMBOL bool
	full() const;

	SGE_TEXTURE_SYMBOL void
	manager(
		texture::manager *
	);

	SGE_TEXTURE_SYMBOL texture::manager *
	manager() const;

	SGE_TEXTURE_SYMBOL void
	virtual on_return_fragment(
		part const &
	) = 0;

	SGE_TEXTURE_SYMBOL void
	container_position(
		detail::container_position const &
	);
private:
	texture::manager *manager_;

	detail::optional_container_position iterator_;
};

}
}

#endif

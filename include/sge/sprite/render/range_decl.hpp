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


#ifndef SGE_SPRITE_RENDER_RANGE_DECL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_DECL_HPP_INCLUDED

#include <sge/sprite/detail/render/range_object.hpp>
#include <sge/sprite/render/range_fwd.hpp>
#include <sge/sprite/render/range_part_decl.hpp>
#include <sge/sprite/render/range_part_vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Choices
>
class range
{
	FCPPT_NONCOPYABLE(
		range
	);
public:
	typedef
	sge::sprite::detail::render::range_object<
		Choices
	>
	range_object;

	typedef
	sge::sprite::render::range_part<
		Choices
	>
	range_part_type;

	typedef
	sge::sprite::render::range_part_vector<
		Choices
	>
	range_part_vector;

	range();

	range(
		range_object const &,
		range_part_vector &&
	);

	range(
		range &&
	);

	range &
	operator=(
		range &&
	);

	~range();

	typedef
	fcppt::optional::reference<
		range_object const
	>
	optional_object;

	optional_object const &
	object() const;

	range_part_vector const &
	parts() const;
private:
	optional_object object_;

	range_part_vector range_parts_;
};

}
}
}

#endif

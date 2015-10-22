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


#ifndef SGE_TEXTURE_BASIC_PART_RAW_HPP_INCLUDED
#define SGE_TEXTURE_BASIC_PART_RAW_HPP_INCLUDED

#include <sge/image/algorithm/uninitialized_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/basic_part_raw_fwd.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/detail/ref_store_type.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>


namespace sge
{
namespace texture
{

template<
	typename Ref
>
class basic_part_raw
:
	public sge::texture::part
{
	FCPPT_NONCOPYABLE(
		basic_part_raw
	);
public:
	typedef
	Ref
	ref_type;

	SGE_TEXTURE_DETAIL_SYMBOL
	explicit
	basic_part_raw(
		ref_type
	);

	SGE_TEXTURE_DETAIL_SYMBOL
	basic_part_raw(
		ref_type,
		sge::renderer::lock_rect const &
	);

	SGE_TEXTURE_DETAIL_SYMBOL
	~basic_part_raw()
	override;

	SGE_TEXTURE_DETAIL_SYMBOL
	void
	data(
		sge::image2d::view::const_object const &,
		sge::image::algorithm::uninitialized
	)
	override;

	SGE_TEXTURE_DETAIL_SYMBOL
	sge::renderer::lock_rect
	area() const
	override;

	SGE_TEXTURE_DETAIL_SYMBOL
	sge::renderer::texture::planar &
	texture() const
	override;

	SGE_TEXTURE_DETAIL_SYMBOL
	bool
	repeatable() const
	override;
private:
	typedef
	typename
	sge::texture::detail::ref_store_type<
		Ref
	>::type
	store_type;

	store_type texture_;

	typedef
	fcppt::optional<
		sge::renderer::lock_rect
	>
	optional_rect;

	optional_rect const area_;
};

}
}

#endif

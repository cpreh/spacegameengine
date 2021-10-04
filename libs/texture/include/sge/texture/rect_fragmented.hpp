//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_RECT_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_RECT_FRAGMENTED_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/color_format_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/optional_part_unique_ptr_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL rect_fragmented
:
	public sge::texture::fragmented
{
	FCPPT_NONMOVABLE(
		rect_fragmented
	);
public:
	SGE_TEXTURE_DETAIL_SYMBOL
	rect_fragmented(
		sge::renderer::device::core_ref,
		sge::renderer::texture::color_format const &,
		sge::renderer::texture::mipmap::object const &,
		sge::renderer::dim2 const &initial_size
	);

	SGE_TEXTURE_DETAIL_SYMBOL
	~rect_fragmented()
	override;
private:
	[[nodiscard]]
	sge::texture::optional_part_unique_ptr
	consume_fragment(
		sge::renderer::dim2 const &
	)
	override;

	void
	return_fragment(
		sge::texture::part const &
	)
	override;

	[[nodiscard]]
	sge::renderer::texture::planar &
	texture()
	override;

	[[nodiscard]]
	sge::renderer::texture::planar const &
	texture() const
	override;

	[[nodiscard]]
	bool
	repeatable() const
	override;

	[[nodiscard]]
	bool
	empty() const
	override;

	sge::renderer::size_type cur_x_;

	sge::renderer::size_type cur_y_;

	sge::renderer::size_type cur_height_;

	sge::renderer::texture::planar_unique_ptr const texture_;

	sge::renderer::size_type texture_count_;
};

}

#endif

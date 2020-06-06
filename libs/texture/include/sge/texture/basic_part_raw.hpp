//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object_decl.hpp>


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
	FCPPT_NONMOVABLE(
		basic_part_raw
	);
public:
	using
	ref_type
	=
	Ref;

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

	[[nodiscard]]
	SGE_TEXTURE_DETAIL_SYMBOL
	sge::renderer::lock_rect
	area() const
	override;

	[[nodiscard]]
	SGE_TEXTURE_DETAIL_SYMBOL
	sge::renderer::texture::planar &
	texture() const
	override;

	[[nodiscard]]
	SGE_TEXTURE_DETAIL_SYMBOL
	bool
	repeatable() const
	override;
private:
	using
	store_type
	=
	typename
	sge::texture::detail::ref_store_type<
		Ref
	>::type;

	store_type texture_;

	using
	optional_rect
	=
	fcppt::optional::object<
		sge::renderer::lock_rect
	>;

	optional_rect const area_;
};

}
}

#endif

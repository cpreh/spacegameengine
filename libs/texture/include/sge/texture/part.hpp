//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_PART_HPP_INCLUDED
#define SGE_TEXTURE_PART_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL part
{
	FCPPT_NONCOPYABLE(
		part
	);
protected:
	SGE_TEXTURE_DETAIL_SYMBOL
	part();
public:
	SGE_TEXTURE_DETAIL_SYMBOL
	virtual
	~part();

	virtual
	void
	data(
		sge::image2d::view::const_object const &,
		sge::image::algorithm::uninitialized
	) = 0;

	virtual
	sge::renderer::lock_rect
	area() const = 0;

	SGE_TEXTURE_DETAIL_SYMBOL
	sge::renderer::dim2
	size() const;

	virtual
	sge::renderer::texture::planar &
	texture() const = 0;

	virtual
	bool
	repeatable() const = 0;
};

}
}

#endif

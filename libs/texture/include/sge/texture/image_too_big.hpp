//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_IMAGE_TOO_BIG_HPP_INCLUDED
#define SGE_TEXTURE_IMAGE_TOO_BIG_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/texture/exception.hpp>
#include <sge/texture/detail/symbol.hpp>


namespace sge
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL image_too_big
:
	public sge::texture::exception
{
public:
	SGE_TEXTURE_DETAIL_SYMBOL
	explicit
	image_too_big(
		sge::renderer::dim2 const &
	);

	SGE_TEXTURE_DETAIL_SYMBOL
	image_too_big(
		image_too_big &&
	)
	noexcept;

	SGE_TEXTURE_DETAIL_SYMBOL
	image_too_big(
		image_too_big const &
	);

	SGE_TEXTURE_DETAIL_SYMBOL
	image_too_big &
	operator=(
		image_too_big &&
	)
	noexcept;

	SGE_TEXTURE_DETAIL_SYMBOL
	image_too_big &
	operator=(
		image_too_big const &
	);

	SGE_TEXTURE_DETAIL_SYMBOL
	~image_too_big() noexcept
	override;
};

}
}

#endif

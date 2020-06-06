//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/dim2.hpp>
#include <sge/texture/exception.hpp>
#include <sge/texture/image_too_big.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/output.hpp>


sge::texture::image_too_big::image_too_big(
	sge::renderer::dim2 const &_size
)
:
	sge::texture::exception(
		(
			fcppt::format(
				FCPPT_TEXT("texture::manager::add() image of size %1% too big!")
			)
			%
			_size
		).str()
	)
{
}

sge::texture::image_too_big::image_too_big(
	image_too_big &&
)
noexcept
= default;

sge::texture::image_too_big::image_too_big(
	image_too_big const &
)
= default;

sge::texture::image_too_big &
sge::texture::image_too_big::operator=(
	image_too_big &&
)
noexcept
= default;

sge::texture::image_too_big &
sge::texture::image_too_big::operator=(
	image_too_big const &
)
= default;

sge::texture::image_too_big::~image_too_big()
noexcept
= default;

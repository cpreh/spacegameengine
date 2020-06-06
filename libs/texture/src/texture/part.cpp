//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/texture/part.hpp>


sge::texture::part::part()
= default;

sge::texture::part::~part()
= default;

sge::renderer::dim2
sge::texture::part::size() const
{
	return
		this->area().size();
}

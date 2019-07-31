//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/dim2.hpp>
#include <sge/texture/atlasing/border_size.hpp>
#include <sge/texture/atlasing/size.hpp>


sge::renderer::dim2
sge::texture::atlasing::size(
	sge::renderer::dim2 const &_dim
)
{
	return
		sge::renderer::dim2(
			sge::texture::atlasing::border_size(
				_dim.w()
			),
			sge::texture::atlasing::border_size(
				_dim.h()
			)
		);
}

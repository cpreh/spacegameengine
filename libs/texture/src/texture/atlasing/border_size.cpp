//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/size_type.hpp>
#include <sge/texture/atlasing/border_size.hpp>
#include <sge/texture/atlasing/gap.hpp>


sge::renderer::size_type
sge::texture::atlasing::border_size(
	sge::renderer::size_type const _size
)
{
	return
		_size + 2U * sge::texture::atlasing::gap();
}

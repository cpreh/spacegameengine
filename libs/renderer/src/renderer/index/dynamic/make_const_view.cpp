//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/make_const_view.hpp>
#include <sge/renderer/index/dynamic/view.hpp>


sge::renderer::index::dynamic::const_view
sge::renderer::index::dynamic::make_const_view(
	sge::renderer::index::dynamic::view const &_view
)
{
	return
		{
			_view.data(),
			_view.size(),
			_view.format()
		};
}

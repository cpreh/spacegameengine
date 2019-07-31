//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/texture/mipmap/level_count_visitor.hpp>
#include <sge/renderer/texture/mipmap/levels_rep.hpp>

sge::d3d9::texture::mipmap::level_count_visitor::result_type
sge::d3d9::texture::mipmap::level_count_visitor::operator()(
	renderer::texture::mipmap::all_levels_rep const &
) const
{
	return 0u;
}

sge::d3d9::texture::mipmap::level_count_visitor::result_type
sge::d3d9::texture::mipmap::level_count_visitor::operator()(
	renderer::texture::mipmap::levels_rep const &_rep
) const
{
	return _rep.value().get();
}

sge::d3d9::texture::mipmap::level_count_visitor::result_type
sge::d3d9::texture::mipmap::level_count_visitor::operator()(
	renderer::texture::mipmap::off_rep const &
) const
{
	return 1u;
}

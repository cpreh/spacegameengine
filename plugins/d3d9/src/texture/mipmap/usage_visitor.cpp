//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/texture/usage.hpp>
#include <sge/d3d9/texture/mipmap/auto_generate_usage.hpp>
#include <sge/d3d9/texture/mipmap/usage_visitor.hpp>
#include <sge/renderer/texture/mipmap/all_levels_rep.hpp>
#include <sge/renderer/texture/mipmap/levels_rep.hpp>


sge::d3d9::texture::mipmap::usage_visitor::result_type
sge::d3d9::texture::mipmap::usage_visitor::operator()(
	sge::renderer::texture::mipmap::all_levels_rep const &_all_levels
) const
{
	return
		sge::d3d9::texture::mipmap::auto_generate_usage(
			_all_levels.auto_generate()
		);
}

sge::d3d9::texture::mipmap::usage_visitor::result_type
sge::d3d9::texture::mipmap::usage_visitor::operator()(
	sge::renderer::texture::mipmap::levels_rep const &_levels
) const
{
	return
		sge::d3d9::texture::mipmap::auto_generate_usage(
			_levels.auto_generate()
		);
}

sge::d3d9::texture::mipmap::usage_visitor::result_type
sge::d3d9::texture::mipmap::usage_visitor::operator()(
	sge::renderer::texture::mipmap::off_rep const &
) const
{
	return
		sge::d3d9::usage(
			0u
		);
}

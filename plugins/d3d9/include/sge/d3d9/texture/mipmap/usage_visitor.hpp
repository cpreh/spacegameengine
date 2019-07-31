//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTURE_MIPMAP_USAGE_VISITOR_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_MIPMAP_USAGE_VISITOR_HPP_INCLUDED

#include <sge/d3d9/usage.hpp>
#include <sge/renderer/texture/mipmap/all_levels_rep_fwd.hpp>
#include <sge/renderer/texture/mipmap/levels_rep_fwd.hpp>
#include <sge/renderer/texture/mipmap/off_rep_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace texture
{
namespace mipmap
{

class usage_visitor
{
public:
	typedef d3d9::usage result_type;

	result_type
	operator()(
		renderer::texture::mipmap::all_levels_rep const &
	) const;

	result_type
	operator()(
		renderer::texture::mipmap::levels_rep const &
	) const;

	result_type
	operator()(
		renderer::texture::mipmap::off_rep const &
	) const;
};

}
}
}
}

#endif

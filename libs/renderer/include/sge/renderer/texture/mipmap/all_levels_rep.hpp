//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_MIPMAP_ALL_LEVELS_REP_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_MIPMAP_ALL_LEVELS_REP_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/mipmap/all_levels_rep_fwd.hpp>
#include <sge/renderer/texture/mipmap/auto_generate.hpp>


namespace sge::renderer::texture::mipmap
{

class all_levels_rep
{
public:
	explicit
	all_levels_rep(
		sge::renderer::texture::mipmap::auto_generate
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::texture::mipmap::auto_generate
	auto_generate() const;
private:
	sge::renderer::texture::mipmap::auto_generate auto_generate_;
};

}

#endif

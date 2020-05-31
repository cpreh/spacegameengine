//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_BASE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/texture/capabilities_field_fwd.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
	FCPPT_NONMOVABLE(
		base
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	base();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~base();

	[[nodiscard]]
	virtual
	sge::renderer::resource_flags_field
	resource_flags() const = 0;

	[[nodiscard]]
	virtual
	sge::renderer::texture::capabilities_field
	capabilities() const = 0;

	[[nodiscard]]
	virtual
	sge::renderer::texture::mipmap::object
	mipmap() const = 0;

	[[nodiscard]]
	virtual
	sge::renderer::texture::mipmap::level_count
	levels() const = 0;

	virtual
	void
	generate_mipmaps() = 0;
};

}
}
}

#endif

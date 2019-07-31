//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_FRAGMENTED_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/fragmented_fwd.hpp>
#include <sge/texture/optional_part_unique_ptr_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL fragmented
{
	FCPPT_NONCOPYABLE(
		fragmented
	);
protected:
	SGE_TEXTURE_DETAIL_SYMBOL
	fragmented();
public:
	SGE_TEXTURE_DETAIL_SYMBOL
	virtual
	~fragmented();

	virtual
	sge::texture::optional_part_unique_ptr
	consume_fragment(
		sge::renderer::dim2 const &
	) = 0;

	virtual
	void
	return_fragment(
		sge::texture::part const &
	) = 0;

	virtual
	sge::renderer::texture::planar &
	texture() = 0;

	virtual
	sge::renderer::texture::planar const &
	texture() const = 0;

	virtual
	bool
	repeatable() const = 0;

	virtual
	bool
	empty() const = 0;
};

}
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_BUFFERS_PARAMETERS_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/buffers/parameters_fwd.hpp>
#include <sge/sprite/detail/symbol.hpp>


namespace sge
{
namespace sprite
{
namespace buffers
{

class parameters
{
public:
	SGE_SPRITE_DETAIL_SYMBOL
	parameters(
		sge::renderer::device::core_ref,
		sge::renderer::vertex::const_declaration_ref
	);

	[[nodiscard]]
	SGE_SPRITE_DETAIL_SYMBOL
	sge::renderer::device::core &
	device() const;

	[[nodiscard]]
	SGE_SPRITE_DETAIL_SYMBOL
	sge::renderer::vertex::declaration const &
	vertex_declaration() const;
private:
	sge::renderer::device::core_ref device_;

	sge::renderer::vertex::const_declaration_ref vertex_declaration_;
};

}
}
}

#endif

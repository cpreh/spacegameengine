//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_BUFFERS_PARAMETERS_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/buffers/parameters_fwd.hpp>
#include <sge/sprite/detail/symbol.hpp>
#include <fcppt/reference_impl.hpp>


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
		sge::renderer::device::core &,
		sge::renderer::vertex::declaration const &
	);

	SGE_SPRITE_DETAIL_SYMBOL
	sge::renderer::device::core &
	device() const;

	SGE_SPRITE_DETAIL_SYMBOL
	sge::renderer::vertex::declaration const &
	vertex_declaration() const;
private:
	fcppt::reference<
		sge::renderer::device::core
	> device_;

	fcppt::reference<
		sge::renderer::vertex::declaration const
	> vertex_declaration_;
};

}
}
}

#endif

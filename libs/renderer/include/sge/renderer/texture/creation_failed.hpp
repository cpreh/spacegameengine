//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_CREATION_FAILED_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CREATION_FAILED_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL creation_failed
:
	public sge::renderer::exception
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	creation_failed(
		fcppt::string &&
	);

	SGE_RENDERER_DETAIL_SYMBOL
	creation_failed(
		creation_failed &&
	);

	SGE_RENDERER_DETAIL_SYMBOL
	creation_failed(
		creation_failed const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	creation_failed &
	operator=(
		creation_failed &&
	);

	SGE_RENDERER_DETAIL_SYMBOL
	creation_failed &
	operator=(
		creation_failed const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~creation_failed() noexcept
	override;
};

}
}
}

#endif

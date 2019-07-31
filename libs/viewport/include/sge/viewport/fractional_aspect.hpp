//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_VIEWPORT_FRACTIONAL_ASPECT_HPP_INCLUDED
#define SGE_VIEWPORT_FRACTIONAL_ASPECT_HPP_INCLUDED

#include <sge/viewport/fractional_aspect_fwd.hpp>
#include <sge/viewport/detail/symbol.hpp>
#include <sge/window/unit.hpp>


namespace sge
{
namespace viewport
{

class fractional_aspect
{
public:
	typedef sge::window::unit value_type;

	SGE_VIEWPORT_DETAIL_SYMBOL
	fractional_aspect(
		value_type num,
		value_type denom
	);

	SGE_VIEWPORT_DETAIL_SYMBOL
	value_type
	num() const;

	SGE_VIEWPORT_DETAIL_SYMBOL
	value_type
	denom() const;
private:
	value_type num_;

	value_type denom_;
};

}
}

#endif

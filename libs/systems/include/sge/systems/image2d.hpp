//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMAGE2D_HPP_INCLUDED
#define SGE_SYSTEMS_IMAGE2D_HPP_INCLUDED

#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>


namespace sge::systems
{

class image2d
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	image2d(
		sge::media::optional_extension_set &&
	);

	[[nodiscard]]
	sge::media::optional_extension_set const &
	extensions() const;
private:
	sge::media::optional_extension_set extensions_;
};

}

#endif

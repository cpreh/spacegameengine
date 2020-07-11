//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_AUDIO_LOADER_HPP_INCLUDED
#define SGE_SYSTEMS_AUDIO_LOADER_HPP_INCLUDED

#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>


namespace sge
{
namespace systems
{

class audio_loader
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	audio_loader(
		sge::media::optional_extension_set &&
	);

	[[nodiscard]]
	sge::media::optional_extension_set const &
	extensions() const;
private:
	sge::media::optional_extension_set extensions_;
};

}
}

#endif

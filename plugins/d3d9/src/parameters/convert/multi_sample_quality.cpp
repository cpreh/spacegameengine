//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/parameters/convert/multi_sample_quality.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples_fwd.hpp>


DWORD
sge::d3d9::parameters::convert::multi_sample_quality(
	sge::renderer::pixel_format::optional_multi_samples const &_samples
)
{
	return 0u; // FIXME!
}

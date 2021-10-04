//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PIXEL_FORMAT_OPTIONAL_MULTI_SAMPLES_FWD_HPP_INCLUDED
#define SGE_RENDERER_PIXEL_FORMAT_OPTIONAL_MULTI_SAMPLES_FWD_HPP_INCLUDED

#include <sge/renderer/pixel_format/multi_samples.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge::renderer::pixel_format
{

using
optional_multi_samples
=
fcppt::optional::object<
	sge::renderer::pixel_format::multi_samples
>;

}

#endif

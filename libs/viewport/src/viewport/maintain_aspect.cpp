//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/fractional_aspect.hpp>
#include <sge/viewport/maintain_aspect.hpp>
#include <sge/viewport/resize_callback.hpp>
#include <sge/viewport/impl/maintain_aspect_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::viewport::resize_callback
sge::viewport::maintain_aspect(
	sge::viewport::fractional_aspect const &_aspect
)
{
	return
		sge::viewport::resize_callback{
			std::bind(
				&sge::viewport::impl::maintain_aspect_function,
				std::placeholders::_1,
				_aspect
			)
		};
}

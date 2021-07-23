//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/aspect.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/target/aspect_from_viewport.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


fcppt::optional::object<
	sge::renderer::scalar
>
sge::renderer::target::aspect_from_viewport(
	sge::renderer::target::viewport const &_viewport
)
{
	return
		sge::renderer::aspect(
			fcppt::math::dim::structure_cast<
				sge::renderer::screen_size,
				fcppt::cast::to_unsigned_fun
			>(
				_viewport.get().size()
			)
		);
}

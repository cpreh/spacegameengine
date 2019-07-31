//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/option_to_resource_flags.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::resource_flags_field
sge::sprite::buffers::option_to_resource_flags(
	sge::sprite::buffers::option const _options
)
{
	switch(
		_options
	)
	{
	case sge::sprite::buffers::option::static_:
		return
			sge::renderer::resource_flags_field::null();
	case sge::sprite::buffers::option::dynamic:
		return
			sge::renderer::resource_flags_field{
				sge::renderer::resource_flags::dynamic
			};
	}

	FCPPT_ASSERT_UNREACHABLE;
}

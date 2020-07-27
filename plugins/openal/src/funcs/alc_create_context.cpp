//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/exception.hpp>
#include <sge/openal/alc.hpp>
#include <sge/openal/check_alc_state.hpp>
#include <sge/openal/funcs/alc_create_context.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/post.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


ALCcontext *
sge::openal::funcs::alc_create_context(
	fcppt::reference<
		ALCdevice
	> const _device
)
{
	std::array<
		ALCint,
		1U
	> const attributes = {{
		0
	}};

	ALCcontext *const result(
		::alcCreateContext(
			&_device.get(),
			attributes.data()
		)
	);

	SGE_OPENAL_CHECK_ALC_STATE(
		_device.get(),
		FCPPT_TEXT("alcCreateContext failed"),
		sge::audio::exception
	)

	FCPPT_ASSERT_POST(
		result,
		sge::audio::exception
	);

	return
		result;
}

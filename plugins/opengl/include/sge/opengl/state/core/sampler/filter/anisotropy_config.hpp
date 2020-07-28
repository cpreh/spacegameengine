//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_FILTER_ANISOTROPY_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_FILTER_ANISOTROPY_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_config_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace sampler
{
namespace filter
{

class anisotropy_config
{
public:
	anisotropy_config(
		GLenum anisotropy_flag,
		GLenum max_anisotropy_flag
	);

	[[nodiscard]]
	GLenum
	anisotropy_flag() const;

	[[nodiscard]]
	GLenum
	max_anisotropy_flag() const;
private:
	GLenum anisotropy_flag_;

	GLenum max_anisotropy_flag_;
};

}
}
}
}
}
}

#endif

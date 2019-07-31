//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_VOLUME_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_VOLUME_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <sge/opengl/texture/optional_volume_config.hpp>
#include <sge/opengl/texture/volume_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class volume_context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		volume_context
	);
public:
	typedef
	sge::opengl::info::context const &
	parameter;

	explicit
	volume_context(
		sge::opengl::info::context const &
	);

	~volume_context()
	override;

	sge::opengl::texture::optional_volume_config const &
	config() const;

	static sge::opengl::context::id const static_id;
private:
	sge::opengl::texture::optional_volume_config const config_;
};

}
}
}

#endif

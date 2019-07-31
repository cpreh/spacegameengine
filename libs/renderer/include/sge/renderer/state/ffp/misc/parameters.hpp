//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_MISC_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_MISC_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <sge/renderer/state/ffp/misc/local_viewer.hpp>
#include <sge/renderer/state/ffp/misc/normalize_normals.hpp>
#include <sge/renderer/state/ffp/misc/parameters_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace misc
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::state::ffp::misc::enable_point_sprites,
		sge::renderer::state::ffp::misc::local_viewer,
		sge::renderer::state::ffp::misc::normalize_normals
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::misc::enable_point_sprites
	enable_point_sprites() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::misc::local_viewer
	local_viewer() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::misc::normalize_normals
	normalize_normals() const;
private:
	sge::renderer::state::ffp::misc::enable_point_sprites enable_point_sprites_;

	sge::renderer::state::ffp::misc::local_viewer local_viewer_;

	sge::renderer::state::ffp::misc::normalize_normals normalize_normals_;
};

}
}
}
}
}

#endif

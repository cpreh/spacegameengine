//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_DEFAULT_TARGET_HPP_INCLUDED
#define SGE_CEGUI_IMPL_DEFAULT_TARGET_HPP_INCLUDED

#include <sge/cegui/impl/optional_render_context_ref.hpp>
#include <sge/cegui/impl/fwds/vector2f_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/state/ffp/transform/optional_object_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Rect.h>
#include <CEGUI/RenderTarget.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class GeometryBuffer;
class RenderQueue;
}

namespace sge
{
namespace cegui
{
namespace impl
{

class default_target
:
	public CEGUI::RenderTarget
{
	FCPPT_NONMOVABLE(
		default_target
	);
public:
	default_target(
		fcppt::log::object &, // NOLINT)google-runtime-references)
		sge::renderer::device::ffp_ref,
		fcppt::reference<
			sge::cegui::impl::optional_render_context_ref const
		>
	);

	~default_target()
	override;
private:
	void
	draw(
		CEGUI::GeometryBuffer const &
	)
	override;

	void
	draw(
		CEGUI::RenderQueue const &
	)
	override;
public:
	void
	setArea(
		CEGUI::Rectf const &
	)
	override;
private:
	[[nodiscard]]
	CEGUI::Rectf const &
	getArea() const
	override;

	[[nodiscard]]
	bool
	isImageryCache() const
	override;

	void
	activate()
	override;

	void
	deactivate()
	override;

	void
	unprojectPoint(
		CEGUI::GeometryBuffer const &,
		CEGUI::Vector2f const &p_in,
		CEGUI::Vector2f &p_out
	) const
	override;

	fcppt::log::object log_;

	sge::renderer::device::ffp_ref const renderer_;

	CEGUI::Rectf viewport_;

	sge::renderer::state::ffp::transform::optional_object_unique_ptr transform_;

	fcppt::reference<
		sge::cegui::impl::optional_render_context_ref const
	> const render_context_;
};

}
}
}

#endif

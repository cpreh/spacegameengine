#ifndef SGE_GUI_IMPL_RENDERER_SCOPED_HPP_INCLUDED
#define SGE_GUI_IMPL_RENDERER_SCOPED_HPP_INCLUDED

#include <sge/gui/impl/renderer/stateless.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/scoped_decl.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace impl
{
namespace renderer
{

class scoped
:
	public sge::gui::impl::renderer::stateless
{
	FCPPT_NONCOPYABLE(
		scoped
	);
public:
	scoped(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &
	);

	~scoped()
	override;
private:
	typedef
	sge::sprite::state::all_choices sprite_state_choices;

	typedef
	sge::sprite::state::object<
		sprite_state_choices
	>
	sprite_state;

	typedef
	sge::sprite::state::scoped<
		sprite_state_choices
	>
	sprite_scoped_state;

	sprite_state state_;

	sprite_scoped_state const scoped_state_;
};

}
}
}
}

#endif

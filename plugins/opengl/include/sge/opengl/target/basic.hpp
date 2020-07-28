//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TARGET_BASIC_HPP_INCLUDED
#define SGE_OPENGL_TARGET_BASIC_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/target/base.hpp>
#include <sge/opengl/target/context_fwd.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/math/box/object_decl.hpp>


namespace sge
{
namespace opengl
{
namespace target
{

template<
	typename Base
>
class basic // NOLINT(fuchsia-multiple-inheritance)
:
	public Base,
	public sge::opengl::target::base
{
	FCPPT_NONMOVABLE(
		basic
	);
protected:
	basic(
		sge::opengl::context::object_ref,
		sge::renderer::target::viewport const &
	);
public:
	~basic()
	override;
private:
	void
	bind()
	override;

	void
	unbind()
	override;

	void
	viewport(
		sge::renderer::target::viewport const &
	)
	override;

	[[nodiscard]]
	sge::renderer::target::viewport
	viewport() const
	override;

	void
	scissor_area(
		sge::renderer::target::scissor_area const &
	)
	override;

	[[nodiscard]]
	sge::renderer::target::scissor_area
	scissor_area() const
	override;

	void
	clear(
		sge::renderer::clear::parameters const &
	)
	override;

	void
	set_viewport();

	void
	set_scissor_area();

	[[nodiscard]]
	virtual
	sge::renderer::screen_unit
	height() const = 0;

	virtual
	void
	on_bind() = 0;

	virtual
	void
	on_unbind() = 0;

	sge::opengl::target::context &context_;

	bool active_;

	sge::renderer::target::viewport viewport_;

	sge::renderer::target::scissor_area scissor_area_;
};

}
}
}

#endif

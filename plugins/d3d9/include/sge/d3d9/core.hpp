//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_CORE_HPP_INCLUDED
#define SGE_D3D9_CORE_HPP_INCLUDED

#include <sge/renderer/core.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/system_field_fwd.hpp>
#include <sge/window/system_ref.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace sge
{
namespace d3d9
{

class core
:
	public sge::renderer::core
{
	FCPPT_NONCOPYABLE(
		core
	);
public:
	explicit
	core(
		fcppt::log::context_reference
	);

	~core()
	override;
private:
	sge::renderer::system_unique_ptr
	create_system(
		sge::window::system_ref
	)
	override;

	sge::renderer::caps::system_field
	caps() const
	override;

	fcppt::log::object log_;
};

}
}

#endif

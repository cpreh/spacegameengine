//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_RESOURCE_HPP_INCLUDED
#define SGE_D3D9_RESOURCE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/needs_reset_fwd.hpp>
#include <sge/d3d9/resource_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/list_hook.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)
FCPPT_PP_DISABLE_GCC_WARNING(-Wnon-virtual-dtor)

class resource
:
	public boost::intrusive::list_base_hook<
		boost::intrusive::link_mode<
			boost::intrusive::auto_unlink
		>
	>
{
	FCPPT_NONCOPYABLE(
		resource
	);
public:
	explicit
	resource(
		D3DPOOL
	);

	explicit
	resource(
		sge::d3d9::needs_reset
	);

	virtual
	~resource() = 0;

	void
	loss();

	void
	reset();

	D3DPOOL
	pool() const;

	bool
	needs_reset() const ;
private:
	virtual
	void
	on_loss() = 0;

	virtual
	void
	on_reset() = 0;

	D3DPOOL const pool_;
};

FCPPT_PP_POP_WARNING

}
}

#endif

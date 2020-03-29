//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_IMAGE2D_OBJECT_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_IMAGE2D_OBJECT_HPP_INCLUDED

#include <sge/image2d/multi_system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/plugin/collection_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/impl/image2d/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace image2d
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		fcppt::log::context_reference,
		sge::image2d::plugin::collection const &,
		sge::systems::image2d const &
	);

	~object();

	sge::image2d::system &
	system() const;
private:
	typedef
	fcppt::unique_ptr<
		sge::image2d::multi_system
	>
	image_multi_unique_ptr;

	image_multi_unique_ptr const image_multi_system_;
};

}
}
}
}

#endif

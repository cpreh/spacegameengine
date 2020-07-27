//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_BUFFER_HOLDER_HPP_INCLUDED
#define SGE_OPENAL_BUFFER_HOLDER_HPP_INCLUDED

#include <sge/openal/buffer_id.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>


namespace sge
{
namespace openal
{

class buffer_holder
{
	FCPPT_NONMOVABLE(
		buffer_holder
	);
public:
	explicit
	buffer_holder(
		fcppt::log::object_reference
	);

	~buffer_holder();

	[[nodiscard]]
	sge::openal::buffer_id
	get() const;
private:
	fcppt::log::object_reference const log_;

	sge::openal::buffer_id const buffer_;
};

}
}

#endif

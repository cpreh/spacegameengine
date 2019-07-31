//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_BUFFER_HOLDER_HPP_INCLUDED
#define SGE_OPENAL_BUFFER_HOLDER_HPP_INCLUDED

#include <sge/openal/buffer_id.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace openal
{

class buffer_holder
{
	FCPPT_NONCOPYABLE(
		buffer_holder
	);
public:
	explicit
	buffer_holder(
		fcppt::log::object &
	);

	~buffer_holder();

	sge::openal::buffer_id
	get() const;
private:
	fcppt::log::object &log_;

	sge::openal::buffer_id const buffer_;
};

}
}

#endif

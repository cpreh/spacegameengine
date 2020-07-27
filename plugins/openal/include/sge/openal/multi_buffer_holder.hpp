//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_MULTI_BUFFER_HOLDER_HPP_INCLUDED
#define SGE_OPENAL_MULTI_BUFFER_HOLDER_HPP_INCLUDED

#include <sge/openal/buffer_id_container.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace openal
{

class multi_buffer_holder
{
	FCPPT_NONMOVABLE(
		multi_buffer_holder
	);
public:
	using
	size_type
	=
	sge::openal::buffer_id_container::size_type;

	explicit
	multi_buffer_holder(
		size_type
	);

	~multi_buffer_holder();

	[[nodiscard]]
	sge::openal::buffer_id_container const &
	container() const;
private:
	sge::openal::buffer_id_container const container_;
};

}
}

#endif

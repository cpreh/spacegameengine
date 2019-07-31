//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_BUFFERS_MULTI_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_MULTI_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/multi_fwd.hpp>
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/slice_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace buffers
{

template<
	typename Choices
>
class multi
{
	FCPPT_NONCOPYABLE(
		multi
	);
public:
	typedef
	Choices
	choices;

	multi(
		sge::sprite::buffers::parameters const &,
		sge::sprite::buffers::option
	);

	~multi();

	typedef
	sge::sprite::buffers::slice<
		Choices
	>
	slice_type;

	slice_type
	allocate(
		sge::sprite::count
	);

	sge::sprite::buffers::parameters const &
	parameters() const;
private:
	sge::sprite::buffers::parameters const parameters_;

	sge::sprite::buffers::option const buffers_option_;

	typedef
	sge::sprite::buffers::object<
		Choices
	>
	buffers_object;

	typedef
	std::vector<
		fcppt::unique_ptr<
			buffers_object
		>
	>
	buffer_vector;

	buffer_vector buffers_;
};

}
}
}

#endif

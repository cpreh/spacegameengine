//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_READ_WRAPPER_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_READ_WRAPPER_DECL_HPP_INCLUDED

#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace detail
{

template<
	typename T,
	typename Enable = void
>
class read_wrapper
{
	FCPPT_NONMOVABLE(
		read_wrapper
	);
public:
	read_wrapper();

	~read_wrapper();

	T &
	get();
private:
	T value_;
};

template<
	typename T
>
class read_wrapper<
	T,
	std::enable_if_t<
		std::is_fundamental_v<
			T
		>
	>
>
{
	FCPPT_NONMOVABLE(
		read_wrapper
	);
public:
	read_wrapper();

	~read_wrapper();

	T &
	get();
private:
	T value_;

};

}
}
}
}

#endif

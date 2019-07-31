//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_VIEW_HPP_INCLUDED

#include <sge/core/detail/export_class_declaration.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/const_tag.hpp>
#include <sge/renderer/index/format.hpp>
#include <sge/renderer/index/is_format.hpp>
#include <sge/renderer/index/iterator_fwd.hpp>
#include <sge/renderer/index/view_fwd.hpp>
#include <sge/renderer/index/detail/pp_formats.hpp>
#include <sge/renderer/index/dynamic/basic_view_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

template<
	typename Format
>
class view
{
public:
	static_assert(
		sge::renderer::index::is_format<
			Format
		>::value,
		"sge::renderer::index::view only accepts index formats"
	);

	typedef
	Format
	format_type;

	typedef
	typename
	format_type::index_type
	value_type;

	typedef
	typename
	format_type::pointer
	pointer;

	typedef
	sge::renderer::size_type
	size_type;

	typedef
	sge::renderer::index::iterator<
		Format
	>
	iterator;

	typedef
	sge::renderer::index::dynamic::basic_view<
		std::is_same<
			typename
			Format::constness,
			sge::renderer::index::const_tag
		>::value
	>
	dynamic_view_type;

	SGE_RENDERER_DETAIL_SYMBOL
	view(
		pointer,
		size_type
	);

	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	view(
		dynamic_view_type const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	pointer
	data() const;

	SGE_RENDERER_DETAIL_SYMBOL
	size_type
	size() const;

	SGE_RENDERER_DETAIL_SYMBOL
	iterator
	begin() const;

	SGE_RENDERER_DETAIL_SYMBOL
	iterator
	end() const;
private:
	pointer data_;

	size_type size_;
};

}
}
}

#define SGE_RENDERER_INDEX_DETAIL_DECLARE_VIEW(\
	seq,\
	_,\
	format\
)\
extern \
template \
class \
SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION \
sge::renderer::index::view<\
	format \
> ;

BOOST_PP_SEQ_FOR_EACH(
	SGE_RENDERER_INDEX_DETAIL_DECLARE_VIEW,
	_,
	SGE_RENDERER_INDEX_DETAIL_PP_FORMATS
)

#endif

#include <fcppt/math/static_size.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/object.hpp>
#include <mizuiro/apply_const.hpp>
#include <mizuiro/nonconst_tag.hpp>
#include <mizuiro/raw_pointer.hpp>
#include <mizuiro/raw_value.hpp>
#include <mizuiro/size_type.hpp>
#include <mizuiro/access/raw.hpp>
#include <mizuiro/detail/ignore_effcpp.hpp>
#include <mizuiro/detail/nonassignable.hpp>
#include <mizuiro/detail/pop_warning.hpp>
#include <mizuiro/image/dimension.hpp>
#include <mizuiro/image/format_is_static.hpp>
#include <mizuiro/image/format_store_fwd.hpp>
#include <mizuiro/image/linear_view.hpp>
#include <mizuiro/image/pitch_type.hpp>
#include <mizuiro/image/access/dereference.hpp>
#include <mizuiro/image/access/stride.hpp>
#include <mizuiro/image/algorithm/print.hpp>
#include <mizuiro/image/types/pointer.hpp>
#include <mizuiro/image/types/reference.hpp>
#include <mizuiro/image/types/value_type.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/math/difference_type.hpp>
#include <fcppt/math/static_size.hpp>
#include <fcppt/math/vector/object.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <cstring>
#include <example_main.hpp>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace mylib
{
namespace vector
{

template
<
	typename Type,
	typename Pointer
>
class proxy
{
FCPPT_NONASSIGNABLE(
	proxy);
public:
	typedef Pointer pointer;

	explicit
	proxy(
		pointer const _data)
	:
		data_(
			_data)
	{
	}

	operator Type() const
	{
		Type result;

		std::memcpy(
			&result,
			data_,
			sizeof(
				Type));

		return result;
	}

	proxy &
	operator=(
		Type const &_other)
	{
		std::memcpy(
			data_,
			&_other,
			sizeof(
				Type));

		return *this;
	}
private:
	pointer const data_;
};

template
<
	typename Type,
	typename Pointer
>
class raw_iterator;

template
<
	typename Type,
	typename Pointer
>
struct raw_iterator_base
{
	typedef
	boost::iterator_facade
	<
		raw_iterator
		<
			Type,
			Pointer
		>,
		Type,
		std::random_access_iterator_tag,
		proxy
		<
			Type,
			Pointer
		>,
		fcppt::math::difference_type
	>
	type;
};

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template
<
	typename Type,
	typename Pointer
>
class raw_iterator
:
public
	raw_iterator_base
	<
		Type,
		Pointer
	>::type
{
	typedef typename
	raw_iterator_base
	<
		Type,
		Pointer
	>::type base;
public:
	typedef typename base::value_type value_type;

	typedef typename base::reference reference;

	typedef Pointer pointer;

	typedef typename base::difference_type difference_type;

	typedef typename base::iterator_category iterator_category;

	explicit
	raw_iterator(
		pointer const _data)
	:
		data_(
			_data)
	{
	}

	template<typename OtherPointer>
	raw_iterator(
		raw_iterator
		<
			Type,
			OtherPointer
		> const &_other)
	:
		data_(
			_other.data_)
	{
	}
	private:
	static
	difference_type
	stride()
	{
		return
			static_cast<difference_type>(
				sizeof(
					Type));
	}

	void
	advance(
		difference_type const _diff)
	{
		data_ +=
			this->stride()
			*
			_diff;
	}

	void
	increment()
	{
		data_ +=
			this->stride();
	}

	void
	decrement()
	{
		data_ -=
			this->stride();
	}

	bool
	equal(
		raw_iterator const &_other) const
	{
		return
			data_
			==
			_other.data_;
	}

	reference
	dereference() const
	{
		return
			reference(
				data_
			);
	}

	difference_type
	distance_to(
		raw_iterator const &_other) const
	{
		return
			(
				_other.data_
				-
				data_
			)
			/
			this->stride();
	}

	template
	<
		typename OtherType,
		typename OtherPointer
	>
	friend class raw_iterator;

	friend class boost::iterator_core_access;

	pointer data_;
};

FCPPT_PP_POP_WARNING

template<typename Type>
class raw_view
{
public:
	typedef fcppt::math::size_type size_type;

	typedef unsigned char *pointer;

	typedef unsigned char const *const_pointer;

	typedef proxy<
		Type,
		pointer
	> reference;

	typedef proxy<
		Type,
		const_pointer
	> const_reference;

	typedef raw_iterator<
		Type,
		pointer
	> iterator;

	typedef raw_iterator<
		Type,
		const_pointer
	> const_iterator;

	raw_view(
		pointer const _data,
		size_type const _size)
	:
		data_(
			_data),
		size_(
			_size)
	{
	}

	pointer
	data() const
	{
		return
			data_;
	}

	iterator
	begin() const
	{
		return
			iterator(
				data_);
	}

	size_type
	size() const
	{
		return
			size_;
	}
private:
	pointer data_;
	size_type size_;
};

}
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

namespace fcppt
{
namespace math
{
template<typename T>
struct is_static_storage
<
	mylib::vector::raw_view<T>
>
:
	boost::true_type
{
};
}
}

FCPPT_PP_POP_WARNING


namespace mylib
{

template
<
	typename Dim,
	typename ValueType,
	fcppt::math::size_type Size
>
struct native_format
{
	// Typedefs for mizuiro
	typedef
	Dim
	dim;

	typedef typename
	mizuiro::image::pitch_type
	<
		dim
	>::type
	pitch;

	// Own typedefs
	typedef
	ValueType
	value_type;

	static fcppt::math::size_type const static_size = Size;
};



}

MIZUIRO_DETAIL_IGNORE_EFFCPP

namespace mizuiro
{
namespace image
{

template
<
	typename Dim,
	typename ValueType,
	fcppt::math::size_type Size
>
struct format_is_static
<
	mylib::native_format
	<
		Dim,
		ValueType,
		Size
	>
>
:
	boost::true_type
{
};

namespace types
{

// Kann so bleiben, der Pointer ist einfach nur der rohe Datenspeicher (kommt von dem void* her)
template
<
	typename Dim,
	typename ValueType,
	fcppt::math::size_type Size,
	typename Constness
>
struct pointer
<
	mizuiro::access::raw,
	mylib::native_format
	<
		Dim,
		ValueType,
		Size
	>,
	Constness
>
:
	mizuiro::apply_const
	<
		mizuiro::raw_pointer,
		Constness
	>
{
};

MIZUIRO_DETAIL_POP_WARNING

// < Freundlich> reference ist das, was operator* vom Iterator liefert.

template
<
	typename Dim,
	typename ValueType,
	fcppt::math::size_type Size
>
struct reference
<
	mizuiro::access::raw,
	mylib::native_format
	<
		Dim,
		ValueType,
		Size
	>,
	mizuiro::nonconst_tag
>
{
	typedef
	fcppt::math::vector::object
	<
		ValueType,
		typename fcppt::math::static_size<Size>::type,
		mylib::vector::raw_view<ValueType>
	>
	type;
};

// < Freundlich> value_type ist etwas, das kopierbar ist, und worin man einen Wert eines operator* abspeichern kann, hier T
// Bei Farben wäre value_type halt color::object, und reference wäre color::proxy

template
<
	typename Dim,
	typename ValueType,
	fcppt::math::size_type Size
>
struct value_type
<
	mylib::native_format
	<
		Dim,
		ValueType,
		Size
	>
>
{
	typedef typename
	fcppt::math::vector::static_
	<
		ValueType,
		Size
	>::type
	type;
};

}

namespace access
{

// stride ist eine Funktion, die dem Iterator sagt, wie viele Einheiten er Pointer weiterschieben
// muss, um zum nächsten Element zu kommen.

template
<
	typename Dim,
	typename ValueType,
	fcppt::math::size_type Size
>
struct stride
<
	mizuiro::access::raw,
	mylib::native_format
	<
		Dim,
		ValueType,
		Size
	>
>
{
	static
	mizuiro::size_type
	execute(
		mizuiro::access::raw const &,
		mizuiro::image::format_store
		<
			mylib::native_format
			<
				Dim,
				ValueType,
				Size
			>
		> const &)
	{
		return
			Size
			*
			sizeof(
				ValueType);
	}
};

// dereference ist eine Funktion, die pointer -> reference macht.
// 12:25 < Freundlich> Also z.B.: Wie mache ich aus unsigned char (const) * einen proxy<T (const)> oder so.

template
<
	typename Dim,
	typename ValueType,
	fcppt::math::size_type Size
>
struct dereference
<
	mizuiro::access::raw,
	mylib::native_format
	<
		Dim,
		ValueType,
		Size
	>,
	mizuiro::nonconst_tag
>
{
	typedef
	mizuiro::access::raw
	access;

	typedef
	mylib::native_format
	<
		Dim,
		ValueType,
		Size
	>
	image_format;

	typedef
	mizuiro::nonconst_tag
	constness;

	typedef typename
	mizuiro::image::types::reference
	<
		access,
		image_format,
		constness
	>::type
	result_type;

	typedef typename
	mizuiro::image::types::pointer
	<
		access,
		image_format,
		constness
	>::type
	pointer;

	static
	result_type
	execute(
		mizuiro::access::raw const &,
		pointer const _data,
		mizuiro::image::format_store<image_format> const &)
	{
		return
			result_type(
				typename result_type::storage_type(
					_data,
					Size));
	}
};

}

}
}


int
main()
{
	typedef
	unsigned
	value_type;

	typedef
	mizuiro::image::dimension<2>
	dim2;

	typedef
	mizuiro::image::linear_view
	<
		::mizuiro::access::raw,
		mylib::native_format
		<
			dim2,
			value_type,
			2
		>,
		mizuiro::nonconst_tag
	>
	native_view;

	typedef
	std::vector<mizuiro::raw_value>
	raw_vector;

	dim2 const size(
		10,
		3);

	raw_vector data(
		sizeof(value_type)
		*
		size.content()
		*
		2);

	native_view const view(
		size,
		&data[0]);

	for(
		native_view::iterator it(
			view.begin());
		it != view.end();
		++it)
		(*it)[0] =
			/*
			native_view::iterator::value_type(
				static_cast<value_type>(
					std::distance(
						view.begin(),
						it)),
				0);
				*/
			static_cast<value_type>(
					std::distance(
						view.begin(),
						it));

	mizuiro::image::algorithm::print(
		std::cout,
		view);

	std::cout << '\n';
}

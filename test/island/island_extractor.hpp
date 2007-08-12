#ifndef ISLAND_EXTRACTOR_HPP_INCLUDED
#define ISLAND_EXTRACTOR_HPP_INCLUDED

#include <list>
#include "../../src/math/rect.hpp"
#include "field.hpp"

struct island_extractor
{
	typedef field<float>                                     field_type;
	typedef field_type::dim_type                             dim_type;
	typedef field_type::coord_type                           coord_type;
	typedef field_type::coord_vector_type                    pos_type;
	typedef sge::math::basic_rect<dim_type::value_type>      rect_type;
	typedef std::list<pos_type>                              pixel_list_type;
	typedef std::list<field_type>                            field_list_type;

	island_extractor();
	island_extractor(field_type &);
	void extract_list(field_list_type &fields);
	bool extract(field_type &target);

	private:
	field_type image;

	void reset(field_type &_image);
	void fast_fill(const coord_type &x,const coord_type &y);
	void flood_fill(const coord_type &x,const coord_type &y,pixel_list_type &pixel_list);
	rect_type bounding_rect(const pixel_list_type &pixel_list) const;
};

#endif

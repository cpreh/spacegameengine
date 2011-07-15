/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/model/obj/instance.hpp>
#include <sge/exception.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/utf8/string.hpp>
#include <fcppt/utf8/from_std_string.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/container/array_fusion.hpp>
#include <fcppt/math/vector/vector.hpp>
#include <boost/fusion/container/vector/vector10.hpp>
#include <boost/spirit/include/qi.hpp>
#include <string>

sge::model::obj::instance::instance(
	fcppt::filesystem::path const &f)
{
	obj::group_sequence current_groups;
	obj::object_sequence current_objects;

	unsigned line_no = 0;
	fcppt::io::cifstream stream(
		f);

	if(!stream.is_open())
		throw 
			sge::exception(
				FCPPT_TEXT("Couldn't open file \"")+
				fcppt::filesystem::path_to_string(
					f)+
				FCPPT_TEXT("\n"));

	std::string line;
	while(
		std::getline(
			stream,
			line))
	{
		++line_no;

		fcppt::utf8::string const line_utf8(
			fcppt::utf8::from_std_string(
				line));

		namespace qi = boost::spirit::qi;
		namespace encoding = qi::standard_wide;

		typedef
		fcppt::string::const_iterator
		iterator;

		typedef
		qi::rule<iterator,encoding::space_type>
		void_rule;

		typedef
		qi::real_policies<obj::scalar>
		scalar_parser;

		typedef
		boost::fusion::vector4<float,float,float,float>
		fusion_vector;

		void_rule comment = 
			qi::lit(FCPPT_TEXT('#')) >> *encoding::char_;
		qi::rule<iterator,encoding::space_type,fusion_vector()> vertex = 
			qi::lit(FCPPT_TEXT('v')) >> qi::float_ >> qi::float_ >> qi::float_ >> qi::float_;
		qi::rule<iterator,encoding::space_type> mtllib = 
			qi::lit(FCPPT_TEXT("mtllib")) >> (+encoding::char_);
		//qi::rule<iterator> line = 
			//comment | vertex | mtllib | object | group | usemtl | smoothing_group | face;
	}
}

sge::model::obj::vertex_sequence const
sge::model::obj::instance::vertices() const
{
	return 
		vertices_;
}

sge::model::obj::texcoord_sequence const
sge::model::obj::instance::texcoords() const
{
	return 
		texcoords_;
}

sge::model::obj::normal_sequence const
sge::model::obj::instance::normals() const
{
	return 
		normals_;
}

sge::model::obj::group_sequence const
sge::model::obj::instance::groups() const
{
	return 
		groups_;
}

sge::model::obj::object_sequence const
sge::model::obj::instance::objects() const
{
	return 
		objects_;
}

sge::model::obj::face_sequence const
sge::model::obj::instance::group_faces(
	obj::group_name const &_name)
{
	return
		obj::face_sequence();
}

sge::model::obj::face_sequence const
sge::model::obj::instance::object_faces(
	obj::object_name const &_name)
{
	return
		obj::face_sequence();
}

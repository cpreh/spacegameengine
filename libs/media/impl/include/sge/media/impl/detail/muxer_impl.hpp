//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_IMPL_DETAIL_MUXER_IMPL_HPP_INCLUDED
#define SGE_MEDIA_IMPL_DETAIL_MUXER_IMPL_HPP_INCLUDED

#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/load_stream_result.hpp>
#include <sge/media/muxer_parameters.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/media/impl/log_name.hpp>
#include <sge/media/impl/detail/muxer.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/object.hpp>
#include <fcppt/const.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/loop.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/fold_break.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/container/set_intersection.hpp>
#include <fcppt/container/set_union.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <typeinfo>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

template<
	typename System,
	typename File
>
sge::media::detail::muxer<
	System,
	File
>::muxer(
	parameters const &_parameters
)
:
	log_{
		_parameters.log_context(),
		sge::log::location(),
		sge::log::default_parameters(
			sge::media::impl::log_name()
		)
	},
	plugins_(
		fcppt::algorithm::map_optional<
			plugin_system_pair_container
		>(
			_parameters.collection(),
			[
				this,
				&_parameters
			](
				sge::plugin::context<
					System
				> const &_context
			)
			{
				plugin_type plugin(
					_context.load()
				);

				system_unique_ptr system_instance(
					plugin.get()(
						_parameters.log_context()
					)
				);

				using
				optional_plugin_system_pair
				=
				fcppt::optional::object<
					plugin_system_pair
				>;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
				optional_plugin_system_pair result(
					fcppt::optional::maybe(
						_parameters.extensions(),
						fcppt::const_(
							true
						),
						[
							&system_instance
						](
							sge::media::extension_set const &_extensions
						)
						{
							return
								!fcppt::container::set_intersection(
									_extensions,
									system_instance->extensions()
								).empty();
						}
					)
					?
						optional_plugin_system_pair(
							std::make_pair(
								std::move(
									plugin
								),
								std::move(
									system_instance
								)
							)
						)
					:
						optional_plugin_system_pair()
				);
FCPPT_PP_POP_WARNING

				if(
					!result.has_value()
				)
					FCPPT_LOG_DEBUG(
						this->log_,
						fcppt::log::out
							<<
							FCPPT_TEXT("System ")
							<<
							fcppt::from_std_string(
								fcppt::type_name_from_info(
									typeid(
										system
									)
								)
							)
							<<
							FCPPT_TEXT(" didn't find plugin ")
							<<
							fcppt::filesystem::path_to_string(
								_context.path()
							)
							<<
							FCPPT_TEXT(" to be useful.")
					)

				return
					result;
			}
		)
	),
	extensions_(
		fcppt::algorithm::fold(
			this->plugins_,
			sge::media::extension_set(),
			[](
				plugin_system_pair const &_plugin,
				sge::media::extension_set const &_state
			)
			{
				return
					fcppt::container::set_union(
						_plugin.second->extensions(),
						_state
					);

			}
		)
	)
{
	FCPPT_LOG_DEBUG(
		this->log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("Available extensions for system ")
			<<
			fcppt::from_std_string(
				fcppt::type_name_from_info(
					typeid(
						system
					)
				)
			)
			<<
			FCPPT_TEXT(" are ")
			<<
			fcppt::container::output(
				this->extensions_
			)
			<<
			FCPPT_TEXT('.')
	)
}

FCPPT_PP_POP_WARNING

template<
	typename System,
	typename File
>
sge::media::detail::muxer<
	System,
	File
>::~muxer<
	System,
	File
>()
= default;

template<
	typename System,
	typename File
>
typename
sge::media::detail::muxer<
	System,
	File
>::load_stream_result
sge::media::detail::muxer<
	System,
	File
>::mux_stream(
	sge::media::stream_unique_ptr &&_stream,
	sge::media::optional_extension const &_opt_extension,
	sge::media::optional_name const &_name
) const
{
	return
		fcppt::optional::maybe(
			_opt_extension,
			[
				this,
				&_stream,
				&_name
			]{
				return
					this->mux_stream_try_all(
						std::move(
							_stream
						),
						_name
					);
			},
			[
				this,
				&_stream,
				&_name
			](
				sge::media::extension const &_extension
			)
			{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
				return
					fcppt::optional::maybe(
						this->mux_extension(
							_extension
						),
						[
							&_stream
						]{
							return
								load_stream_result(
									std::move(
										_stream
									)
								);
						},
						[
							&_extension,
							&_stream,
							&_name
						](
							fcppt::reference<
								System
							> const _system
						)
						{
							return
								_system.get().load_stream(
									std::move(
										_stream
									),
									sge::media::optional_extension(
										_extension
									),
									_name
								);
						}
					);
FCPPT_PP_POP_WARNING
			}
		);
}

template<
	typename System,
	typename File
>
typename
sge::media::detail::muxer<
	System,
	File
>::optional_system_ref
sge::media::detail::muxer<
	System,
	File
>::mux_extension(
	sge::media::extension const &_extension
) const
{
	return
		fcppt::optional::map(
			fcppt::algorithm::find_if_opt(
				plugins_,
				[
					&_extension
				](
					plugin_system_pair const &_plugin
				)
				{
					return
						fcppt::algorithm::contains(
							_plugin.second->extensions(),
							_extension
						);
				}
			),
			[](
				auto const _iterator
			)
			{
				return
					fcppt::make_ref(
						*_iterator->second
					);
			}
		);
}

template<
	typename System,
	typename File
>
sge::media::extension_set
sge::media::detail::muxer<
	System,
	File
>::extensions() const
{
	return
		extensions_;
}

template<
	typename System,
	typename File
>
typename
sge::media::detail::muxer<
	System,
	File
>::load_stream_result
sge::media::detail::muxer<
	System,
	File
>::mux_stream_try_all(
	sge::media::stream_unique_ptr &&_stream,
	sge::media::optional_name const &_name
) const
{
	return
		fcppt::algorithm::fold_break(
			plugins_,
			load_stream_result{
				std::move(
					_stream
				)
			},
			[
				&_name
			](
				plugin_system_pair const &_plugin,
				load_stream_result &&_cur
			)
			{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
				return
					fcppt::variant::match(
						std::move(
							_cur
						),
						[
							&_name,
							&_plugin
						](
							sge::media::stream_unique_ptr &&_cur_stream
						)
						{
							// TODO(philipp): This doesn't need to be done in the first iteration
							_cur_stream->seekg(
								0,
								std::ios_base::beg
							);

							return
								std::make_pair(
									fcppt::loop::continue_,
									_plugin.second->load_stream(
										std::move(
											_cur_stream
										),
										sge::media::optional_extension(),
										_name
									)
								);
						},
						[](
							file_unique_ptr &&_file
						)
						{
							return
								std::make_pair(
									fcppt::loop::break_,
									load_stream_result{
										std::move(
											_file
										)
									}
								);
						}
					);
FCPPT_PP_POP_WARNING
			}
		);
}

#endif

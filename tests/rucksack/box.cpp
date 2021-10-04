//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/axis_policy2_comparison.hpp>
#include <sge/rucksack/axis_policy2_output.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/box.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/rucksack/widget/reference_alignment.hpp>
#include <sge/rucksack/widget/reference_alignment_container.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_CATCH_BEGIN

TEST_CASE(
	"rucksack::box",
	"[sge]"
)
{
	sge::rucksack::widget::dummy child1{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					0
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			}
		}
	};

	sge::rucksack::widget::box box1{
		sge::rucksack::axis::x,
		sge::rucksack::padding{
			0
		},
		sge::rucksack::widget::reference_alignment_container{
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					child1
				},
				sge::rucksack::alignment::center
			}
		}
	};

	box1.size(
		sge::rucksack::dim{
			100, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			100 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
	);

	CHECK(
		box1.axis_policy()
		==
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					0
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			}
		}
	);

	box1.relayout();

	CHECK(
		child1.size()
		==
		sge::rucksack::dim{
			100, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
	);

	sge::rucksack::widget::dummy child2{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			}
		}
	};

	box1.push_back_child(
		fcppt::reference_to_base<
			sge::rucksack::widget::base
		>(
			fcppt::make_ref(
				child2
			)
		),
		sge::rucksack::alignment::center
	);

	box1.relayout();

	CHECK(
		box1.axis_policy()
		==
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			}
		}
	);

	CHECK(
		child1.size()
		==
		sge::rucksack::dim{
			90, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
	);

	CHECK(
		child2.size()
		==
		sge::rucksack::dim{
			10, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
	);
}

FCPPT_CATCH_BEGIN

TEST_CASE(
	"rucksack::box in box",
	"[sge]"
)
{
	sge::rucksack::widget::dummy child_x_1{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					0
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			}
		}
	};

	sge::rucksack::widget::dummy child_x_2{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					20 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					20 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			}
		}
	};

	sge::rucksack::widget::box box1{
		sge::rucksack::axis::x,
		sge::rucksack::padding{
			0
		},
		sge::rucksack::widget::reference_alignment_container{
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					child_x_1
				},
				sge::rucksack::alignment::center
			},
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					child_x_2
				},
				sge::rucksack::alignment::left_or_top
			}
		}
	};

	sge::rucksack::widget::dummy child_y_1{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					0
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			}
		}
	};

	sge::rucksack::widget::dummy child_y_2{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					0
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					0
				}
			}
		}
	};

	sge::rucksack::widget::box box2{
		sge::rucksack::axis::y,
		sge::rucksack::padding{
			0
		},
		sge::rucksack::widget::reference_alignment_container{
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					box1
				},
				sge::rucksack::alignment::center
			},
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					child_y_1
				},
				sge::rucksack::alignment::center
			},
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					child_y_2
				},
				sge::rucksack::alignment::center
			}
		}
	};

	box2.size(
		sge::rucksack::dim{
			100, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			30 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
	);

	CHECK(
		box2.axis_policy()
		==
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					20 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					30 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				}
			}
		}
	);

	box2.relayout();

	CHECK(
		child_x_1.position()
		==
		sge::rucksack::vector{
			0,
			5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
	);

	CHECK(
		child_x_2.position()
		==
		sge::rucksack::vector{
			80, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			0
		}
	);

	CHECK(
		child_x_1.size()
		==
		sge::rucksack::dim{
			80, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
	);

	CHECK(
		child_x_2.size()
		==
		sge::rucksack::dim{
			20, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			20 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
	);

	CHECK(
		box1.size()
		==
		sge::rucksack::dim{
			100, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			20 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
	);

	CHECK(
		child_y_1.size()
		==
		sge::rucksack::dim{
			100, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
	);

	box1.pop_back_child();

	box1.relayout();

	CHECK(
		box1.position()
		==
		sge::rucksack::vector{
			0,
			0
		}
	);

	box1.push_back_child(
		fcppt::reference_to_base<
			sge::rucksack::widget::base
		>(
			fcppt::make_ref(
				child_x_2
			)
		),
		sge::rucksack::alignment::left_or_top
	);

	box1.relayout();

	CHECK(
		box1.position()
		==
		sge::rucksack::vector{
			0,
			0
		}
	);
}

FCPPT_CATCH_END

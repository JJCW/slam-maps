//
// Copyright (c) 2015-2017, Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.
// Copyright (c) 2015-2017, University of Bremen
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
#define BOOST_TEST_MODULE SerializationTest

#include <fstream>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/iterator/iterator_concepts.hpp>

#include <string.h>
#include <iostream>

#include <maps/grid/DiscreteTree.hpp>
#include <maps/grid/OccupancyPatch.hpp>


using namespace maps::grid;

BOOST_AUTO_TEST_CASE(test_serialization_discrete_tree)
{
    std::string filename = "DiscreteTree_v1.bin";

    // Save.
    std::ofstream output(filename, std::ios::binary);
    if (output.is_open())
    {
        boost::archive::binary_oarchive oa(output);

        DiscreteTree<OccupancyPatch> tree = DiscreteTree<OccupancyPatch>(0.1);

        for (uint i = 0; i < 5; ++i)
        {
            tree.insert(std::pair<int32_t, OccupancyPatch>(i, OccupancyPatch(i / 10.0)));
        }
        BOOST_CHECK_EQUAL(tree.size(), 5);

        oa << tree;
    }

    // Load.
    std::ifstream input(filename, std::ios::binary);
    if (input.is_open())
    {
        boost::archive::binary_iarchive ia(input);

        DiscreteTree<OccupancyPatch> tree(1.0);

        ia >> tree;

        BOOST_CHECK_EQUAL(tree.size(), 5);
        BOOST_CHECK_CLOSE(tree.getResolution(), 0.1, 0.1);

        for (uint i = 0; i < 5; ++i)
        {
             BOOST_CHECK_CLOSE(tree.getCellAt(i).getPropability(), i / 10.0, 0.1);
        }
    }
}

BOOST_AUTO_TEST_CASE(test_serialization_discrete_tree_backwards_compatibility_v0)
{
    // Load v0 discrete tree with:
    int size = 5;
    float resolution = 0.1;
    // OccupancyPatch.getPropability() is 1/10 of the index.

    std::string filename = "DiscreteTree_v0.bin";

    std::ifstream input(filename, std::ios::binary);
    if (input.is_open())
    {
        boost::archive::binary_iarchive ia(input);

        DiscreteTree<OccupancyPatch> tree(1.0);

        ia >> tree;

        BOOST_CHECK_EQUAL(tree.size(), size);
        BOOST_CHECK_CLOSE(tree.getResolution(), resolution, 0.1);

        for (uint i = 0; i < 5; ++i)
        {
             BOOST_CHECK_CLOSE(tree.getCellAt(i).getPropability(), i / 10.0, 0.1);
        }
    }
}




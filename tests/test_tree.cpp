#include <catch2/catch_test_macros.hpp>

#include <TTNS/BFIterator.hpp>
#include <TTNS/Tree.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

TEST_CASE("BFIterator", "[tree]") {
    using Node = TTNS::Node<int>;
    static_assert(std::forward_iterator<Node::Iterator>);
    static_assert(std::forward_iterator<Node::ConstIterator>);

    TTNS::Node<int> root(1);
    root.emplace_child(2);
    root.emplace_child(3);
    root.emplace_child(4);
    REQUIRE(root.get_num_children() == 3);

    root[0].emplace_child(5);
    root[0].emplace_child(6);
    REQUIRE(root[0].get_num_children() == 2);

    root[2].emplace_child(7);
    root[2].emplace_child(8);
    REQUIRE(root[2].get_num_children() == 2);

    root[0][0].emplace_child(9);
    root[0][0].emplace_child(10);
    REQUIRE(root[0][0].get_num_children() == 2);

    root[2][0].emplace_child(11);
    root[2][0].emplace_child(12);
    REQUIRE(root[2][0].get_num_children() == 2);

    SECTION("BF iteration with Iterator") {
        std::vector<int> result;
        std::transform(root.begin_bf(), root.end_bf(),
                       std::back_inserter(result),
                       [](Node &node) { return node.get_data(); });
        REQUIRE(result ==
                std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    }

    SECTION("BF iteration with ConstIterator") {
        std::vector<int> result;
        std::transform(root.cbegin_bf(), root.cend_bf(),
                       std::back_inserter(result),
                       [](const Node &node) { return node.get_data(); });
        REQUIRE(result ==
                std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    }
}
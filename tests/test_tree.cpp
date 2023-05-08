#include <catch2/catch_test_macros.hpp>

#include <TTNS/BFSIterator.hpp>
#include <TTNS/Tree.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

TEST_CASE("BFSIterator", "[tree]") {
  using Node = TTNS::Node<int>;
  static_assert(std::forward_iterator<Node::Iterator>);
  static_assert(std::forward_iterator<Node::ConstIterator>);

  TTNS::Node<int> root(1);
  root.emplace_child(2);
  root.emplace_child(3);
  root.emplace_child(4);

  root[0].emplace_child(5);
  root[0].emplace_child(6);
  root[2].emplace_child(7);
  root[2].emplace_child(8);

  root[0][0].emplace_child(9);
  root[0][0].emplace_child(10);
  root[2][0].emplace_child(11);
  root[2][0].emplace_child(12);

  std::vector<int> result(12);
  std::transform(root.begin(), root.end(), result.begin(),
                 [](Node &node) { return node.get_data(); });
  REQUIRE(result == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

  std::vector<int> result2(12);
  std::transform(root.cbegin(), root.cend(), result2.begin(),
                 [](const Node &node) { return node.get_data(); });
  REQUIRE(result2 == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
}
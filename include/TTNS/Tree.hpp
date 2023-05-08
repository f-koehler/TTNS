#ifndef TTNS_TREE_HPP
#define TTNS_TREE_HPP

#include <queue>
#include <vector>

namespace TTNS {

template <typename Data> class BFSIterator;

template <typename Data> class Node {
public:
  using DataType = Data;
  using Iterator = BFSIterator<Node>;
  using ConstIterator = BFSIterator<const Node>;

private:
  Node *m_parent;
  std::vector<Node> m_children;
  DataType m_data;

public:
  template <typename... Args> explicit Node(Args &&...args);
  virtual ~Node() = default;

  template <typename... Args> void emplace_child(Args &&...args);

  bool is_root() const;
  const std::vector<Node> &get_children() const;
  std::vector<Node> &get_children();
  const DataType &get_data() const;
  DataType &get_data();

  Iterator begin();
  Iterator end();
  ConstIterator cbegin() const;
  ConstIterator cend() const;

  const Node &at(std::size_t index) const;
  Node &at(std::size_t index);

  const Node &operator[](std::size_t index) const;
  Node &operator[](std::size_t index);
};

template <typename Data>
template <typename... Args>
Node<Data>::Node(Args &&...args)
    : m_parent(nullptr), m_children(), m_data(std::forward<Args>(args)...) {}

template <typename Data>
template <typename... Args>
void Node<Data>::emplace_child(Args &&...args) {
  m_children.emplace_back(std::forward<Args>(args)...);
  m_children.back().m_parent = this;
}

template <typename Data> bool Node<Data>::is_root() const {
  return m_parent == nullptr;
}

template <typename Data>
const std::vector<Node<Data>> &Node<Data>::get_children() const {
  return m_children;
}

template <typename Data> std::vector<Node<Data>> &Node<Data>::get_children() {
  return m_children;
}

template <typename Data>
const typename Node<Data>::DataType &Node<Data>::get_data() const {
  return m_data;
}

template <typename Data> typename Node<Data>::DataType &Node<Data>::get_data() {
  return m_data;
}

template <typename Data> typename Node<Data>::Iterator Node<Data>::begin() {
  return Iterator(this);
}

template <typename Data> typename Node<Data>::Iterator Node<Data>::end() {
  return Iterator(nullptr);
}

template <typename Data>
typename Node<Data>::ConstIterator Node<Data>::cbegin() const {
  return ConstIterator(this);
}

template <typename Data>
typename Node<Data>::ConstIterator Node<Data>::cend() const {
  return ConstIterator(nullptr);
}

template <typename Data>
const Node<Data> &Node<Data>::at(std::size_t index) const {
  return m_children.at(index);
}
template <typename Data> Node<Data> &Node<Data>::at(std::size_t index) {
  return m_children.at(index);
}

template <typename Data>
const Node<Data> &Node<Data>::operator[](std::size_t index) const {
  return m_children[index];
}
template <typename Data> Node<Data> &Node<Data>::operator[](std::size_t index) {
  return m_children[index];
}

template <typename NodeT> class BFSIterator {
public:
  using NodeType = NodeT;

  using value_type = NodeType;
  using difference_type = std::ptrdiff_t;
  using reference = NodeType &;
  using pointer = NodeType *;
  using iterator_category = std::forward_iterator_tag;

private:
  std::queue<NodeType *> m_queue;

public:
  BFSIterator() = default;
  explicit BFSIterator(NodeType *node);
  virtual ~BFSIterator() = default;

  NodeType &operator*() const;
  BFSIterator &operator++();
  BFSIterator operator++(int);
  bool operator==(const BFSIterator &other) const;
  bool operator!=(const BFSIterator &other) const;
};

template <typename NodeT>
BFSIterator<NodeT>::BFSIterator(BFSIterator<NodeT>::NodeType *node) {
  if (node != nullptr) {
    m_queue.push(node);
  }
}

template <typename NodeT>
typename BFSIterator<NodeT>::NodeType &BFSIterator<NodeT>::operator*() const {
  return *m_queue.front();
}

template <typename NodeT> BFSIterator<NodeT> &BFSIterator<NodeT>::operator++() {
  if (m_queue.empty()) {
    return *this;
  }

  auto node = m_queue.front();
  m_queue.pop();
  for (auto &child : node->get_children()) {
    m_queue.push(&child);
  }
  return *this;
}

template <typename NodeT>
BFSIterator<NodeT> BFSIterator<NodeT>::operator++(int) {
  BFSIterator copy(*this);
  ++(*this);
  return copy;
}

template <typename NodeT>
bool BFSIterator<NodeT>::operator==(const BFSIterator<NodeT> &other) const {
  if (m_queue.empty() != other.m_queue.empty()) {
    return false;
  }
  if (m_queue.empty()) {
    return true;
  }
  return m_queue.front() == other.m_queue.front();
}

template <typename NodeT>
bool BFSIterator<NodeT>::operator!=(const BFSIterator<NodeT> &other) const {
  return !(*this == other);
}

} // namespace TTNS

#endif /* TTNS_TREE_HPP */

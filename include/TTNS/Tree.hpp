#ifndef TTNS_TREE_HPP
#define TTNS_TREE_HPP

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
  std::size_t get_num_children() const;
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

template <typename Data> std::size_t Node<Data>::get_num_children() const {
  return m_children.size();
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

} // namespace TTNS

#endif /* TTNS_TREE_HPP */

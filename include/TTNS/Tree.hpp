#ifndef TTNS_TREE_HPP
#define TTNS_TREE_HPP

#include <vector>

namespace TTNS {

template <typename Node>
class BFIterator;

template <typename Node>
class DFIterator;

template <typename Data>
class Node {
  public:
    using DataType = Data;

  private:
    Node *m_parent;
    std::vector<Node> m_children;
    DataType m_data;

  public:
    template <typename... Args>
    explicit Node(Args &&...args);
    virtual ~Node() = default;

    template <typename... Args>
    void emplace_child(Args &&...args);

    bool is_root() const;
    std::size_t get_num_children() const;
    const DataType &get_data() const;
    DataType &get_data();

    typename std::vector<Node>::iterator begin();
    typename std::vector<Node>::iterator end();
    typename std::vector<Node>::const_iterator cbegin() const;
    typename std::vector<Node>::const_iterator cend() const;
    BFIterator<Node> begin_bf();
    BFIterator<Node> end_bf();
    BFIterator<const Node> cbegin_bf() const;
    BFIterator<const Node> cend_bf() const;
    DFIterator<Node> begin_df();
    DFIterator<Node> end_df();
    DFIterator<const Node> cbegin_df() const;
    DFIterator<const Node> cend_df() const;

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

template <typename Data>
bool Node<Data>::is_root() const {
    return m_parent == nullptr;
}

template <typename Data>
std::size_t Node<Data>::get_num_children() const {
    return m_children.size();
}

template <typename Data>
const typename Node<Data>::DataType &Node<Data>::get_data() const {
    return m_data;
}

template <typename Data>
typename Node<Data>::DataType &Node<Data>::get_data() {
    return m_data;
}

template <typename Data>
typename std::vector<Node<Data>>::iterator Node<Data>::begin() {
    return m_children.begin();
}
template <typename Data>
typename std::vector<Node<Data>>::iterator Node<Data>::end() {
    return m_children.end();
}
template <typename Data>
typename std::vector<Node<Data>>::const_iterator Node<Data>::cbegin() const {
    return m_children.cbegin();
}
template <typename Data>
typename std::vector<Node<Data>>::const_iterator Node<Data>::cend() const {
    return m_children.cend();
}

template <typename Data>
BFIterator<Node<Data>> Node<Data>::begin_bf() {
    return BFIterator<Node<Data>>(this);
}

template <typename Data>
BFIterator<Node<Data>> Node<Data>::end_bf() {
    return BFIterator<Node<Data>>(nullptr);
}

template <typename Data>
BFIterator<const Node<Data>> Node<Data>::cbegin_bf() const {
    return BFIterator<const Node<Data>>(this);
}

template <typename Data>
BFIterator<const Node<Data>> Node<Data>::cend_bf() const {
    return BFIterator<const Node<Data>>(nullptr);
}

template <typename Data>
DFIterator<Node<Data>> Node<Data>::begin_df() {
    return DFIterator<Node<Data>>(this);
}

template <typename Data>
DFIterator<Node<Data>> Node<Data>::end_df() {
    return DFIterator<Node<Data>>(nullptr);
}

template <typename Data>
DFIterator<const Node<Data>> Node<Data>::cbegin_df() const {
    return DFIterator<const Node<Data>>(this);
}

template <typename Data>
DFIterator<const Node<Data>> Node<Data>::cend_df() const {
    return DFIterator<const Node<Data>>(nullptr);
}

template <typename Data>
const Node<Data> &Node<Data>::at(std::size_t index) const {
    return m_children.at(index);
}
template <typename Data>
Node<Data> &Node<Data>::at(std::size_t index) {
    return m_children.at(index);
}

template <typename Data>
const Node<Data> &Node<Data>::operator[](std::size_t index) const {
    return m_children[index];
}
template <typename Data>
Node<Data> &Node<Data>::operator[](std::size_t index) {
    return m_children[index];
}

} // namespace TTNS

#endif /* TTNS_TREE_HPP */

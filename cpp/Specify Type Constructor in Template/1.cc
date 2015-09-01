


/* multi-paras type constructore as template arguments */
template <typename T, typename G, template <typename,typename> class Container>
T foo(Container<T,G> &container) {
  return container.get(0).first;
}

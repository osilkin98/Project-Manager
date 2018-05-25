#ifndef TRIES_H
#define TRIES_H

#include <string>

typedef struct trie_node {
  trie_node *next, *child;
  int value, div_count;
  char key;
  trie_node(char new_key = '\0', int new_value = -1)
    : key(new_key), value(new_value), next(NULL), child(NULL), div_count(0) { }
} node;

class prefix_trie {
private:
  void remove_nodes(node *to_remove);
  node *root;
public:
  prefix_trie(void);

  template <typename S, template <typename S> typename L>
  prefix_trie(L < S >& iterator);

  ~prefix_trie(void);
  
  // const int remove(const std::string& str);

  template <typename S, template <typename S> typename L>
  void insert(L<S>& list);

  //void insert(std::deque<std::string>& iterator);
  void insert(const std::string& str, const int value);

  const bool contains(const std::string& str) const;

  const int retrieve(const std::string& str) const;
  
  const int retrieve_autocomplete(const std::string& str) const;

  void print(void) const {
    print_nodes(root);
  }
private:
  void print_nodes(node *v) const;
};

#endif

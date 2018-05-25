#include "tries.h"
#include <cctype>
#include <iostream>
#include <vector>
#include <stack>

prefix_trie::prefix_trie(void) : root(NULL) { }

template <typename S, template <typename S> typename L>
prefix_trie::prefix_trie(L<S>& list) {
  insert(list);
}
prefix_trie::~prefix_trie(void) {
  remove_nodes(root);
}

void prefix_trie::remove_nodes(node *to_remove) {
  if(!to_remove) {
    return;
  }
  remove_nodes(to_remove -> child);
  remove_nodes(to_remove -> next);
  delete to_remove;
}
/*
const int remove(const std::string& str) {
  if(contains(str)) {
    node *traversal = root;
    for(
  } else {
    return -1;
  }
  }*/

template <typename S, template <typename S> typename L>
void prefix_trie::insert(L<S>& list) {
  for(register int i = 0; i < list.size(); ++i) {
    insert(list[i], i + 1);
  }
}

void prefix_trie::insert(const std::string& str, const int value) {
  if(!str.size()) {
    return;
  }
  
  if(!root) {
    root = new node(tolower(str[0]));
  }
  std::stack<node *> visited_nodes;
  node *traversal = root;
  for(register size_t i = 0; i < str.size(); ++i) {
    if(traversal -> key != tolower(str[i])) { // going right on our trie tree
      while(traversal -> next) { // while next is not-null
	visited_nodes.push(traversal); // push the current node onto visited nodes stack
	traversal = traversal -> next; // and move to the next
	if(traversal -> key == tolower(str[i])) { // if we find a trie node for our key
	  break; // then we break out of the loop
	}
      }
      visited_nodes.push(traversal); // push current node onto stack
      /* at this point we'd either be at the last node or at a node 
         which has the same key as the current character in the string */
      if(traversal -> key != tolower(str[i])) { 
	// if the case is the former, then we make a new node and just go from there
	traversal -> next = new node(str[i]);
	//++(traversal -> div_count);
	traversal = traversal -> next;
      }
    }
    if(i + 1 < str.size()) { // 0 + 1 < 2; 1 + 1 = 2
      // if we don't have a child
      if(!traversal -> child) {
	// creates a child node as the i+1th element in the string 
	traversal -> child = new node(tolower(str[i+1]));
      }
    } else { // last index of the string
      if(!traversal -> child) { // does not have child
	traversal -> child = new node('\0', value);
      } else { // has child
	node *temp = traversal -> child;
	while(temp -> next) { // while there are multiple children
	  if(temp -> key == '\0') {
	    return;
	  }
	  temp = temp -> next;
	}
	temp -> next = new node('\0', value);
      }
    }
    visited_nodes.push(traversal);
    traversal = traversal -> child;
  }
  int prev_div = 0;
  while(!visited_nodes.empty()) {
    visited_nodes.top() -> div_count = visited_nodes.top() -> next ? visited_nodes.top() -> div_count + 1 : prev_div;
    prev_div = visited_nodes.top() -> div_count;
    visited_nodes.pop();
  }
}


/* 
struct stack_node {
  std::string prefix;
  node *P;
  stack_node(std::string str, node *v) : prefix(str), P(v) { }
};

/*
void prefix_trie::print(void) const {
  if(!v) {
    return;
  }
  std::stack<stack_node> to_print;
  std::string prefix;
  node *traversal = root;
  while(traversal) {
    

    // if we're at a junction, we need to split off 
    if(traversal -> next) {
      to_print.push(stack_node(prefix, traversal -> next));
      to_print.push(stack_node(prefix, traversal));
      
    }
    
  }	
  }*/

const int prefix_trie::retrieve_autocomplete(const std::string& str) const {
  node *iterator = root;
  register size_t i;
  for(i = 0; i < str.size(); ++i) {
    
    if(!iterator) {
      return -1; // doesn't contain
    }
    if(iterator -> div_count > 0) {
      while(iterator -> key != tolower(str[i])) { // selects correct sub-tree
	iterator = iterator -> next;
	if(!iterator) {
	  return -1;
	}
      }
    }
    
    if(i + 1 == str.size()) { // if at last index
      node *temp = iterator -> child;
      while(temp) {
	if(temp -> key == '\0') {
	  return temp -> value;
	}
	temp = temp -> next;
      }
      break;
    }
    iterator = iterator -> child;

  }
  if(iterator) {
    if((tolower(str[i]) == iterator -> key) && !(iterator -> div_count)) {
      while(iterator -> key != '\0') {
	iterator = iterator -> child;
      }
      return iterator -> value;
    }
    return -1;
  } else {
    return -1;
  }
  
}

const int prefix_trie::retrieve(const std::string& str) const {
  node *iterator = root;
  for(register size_t i = 0; i < str.size(); ++i) {
    if(!iterator) {
      return -1; // doesn't contain
    }
    std::cerr << str[i];

    while(iterator -> key != tolower(str[i])) { // selects correct sub-tree
      iterator = iterator -> next;
      if(!iterator) {
	return -1;
      }
    }
    iterator = iterator -> child;

    if(i + 1 == str.size()) { // if at last index
      while(iterator) {
	if(iterator -> key == '\0') {
	  return iterator -> value;
	}
	iterator = iterator -> next;
      }
    }
  }
  return -1;
}

const bool prefix_trie::contains(const std::string& str) const {
  
  node *iterator = root;
  for(register size_t i = 0; i < str.size(); ++i) {
    if(!iterator) {
      return false;
    }
    while(iterator -> key != tolower(str[i])) {
      iterator = iterator -> next;
      if(!iterator) {
	return false;
      }
    }
    iterator = iterator -> child;
  }
  return true;
}

/* FOR DEBUGGING */ 
void prefix_trie::print_nodes(node *v) const {
  if(!v) {
    return;
  }
  if(v -> key == '\0') {
    std::cout << v -> value << '\n';
  } else {
    std::cout << v -> key << " - ";
  }
  print_nodes(v -> child);
  print_nodes(v -> next);
}

int main(void) {
  // std::vector<std::string> strings = {"test", "top", "trap", "train"};
  std::vector<std::string> strings = {"there", "the", "their"};
  // prefix_trie<std::vector< std::string> > my_tries(strings);
  prefix_trie my_tries;
  int i;
  for(i = 0; i < strings.size(); ++i) {
    my_tries.insert(strings[i], i + 1);
  }
  std::cerr << "i: " << i << " : strings.size() = 4\n";
  // std::vector<std::string> tests = {"top", "trap", "test", "TeSt", "tes", "testr", "assert" };
  std::vector<std::string> tests = {"there", "the", "their" };
  /*for(size_t i = 0; i < tests.size(); ++i) {
    if(my_tries.contains(tests[i])) {
      std::cout << "my_tries contains " << tests[i] << "\n";
    } else {
      std::cout << "my_tries does not contain " << tests[i] << "\n";
    }
  }
 
  my_tries.print();
  my_tries.insert(std::string("assert"), 4); 
  my_tries.print();
  for(size_t i = 0; i < tests.size(); ++i) {
    if(my_tries.contains(tests[i])) {
      std::cout << "my_tries contains " << tests[i] << "\n";
    } else {
      std::cout << "my_tries does not contain " << tests[i] << "\n";
    }
  }
   my_tries.insert(tests[2], 5);
  my_tries.print();
  my_tries.insert(tests[3], 6);*/
  my_tries.print(); 

  std::cout << "\n\n";
  for(register size_t i = 0; i < tests.size(); ++i) {
    std::cerr << "value of " << tests[i] << ": "<< my_tries.retrieve_autocomplete(tests[i]) << "\n"; 
  }
  std::cout << std::endl;
  return 0;
}

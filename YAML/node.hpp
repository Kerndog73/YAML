//
//  node.hpp
//  YAML
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <vector>
#include <string>
#include <unordered_map>
#include <boost/variant.hpp>

namespace YAML {
  enum class NodeType {
    UNDEFINED,
    NUL,
    SCALAR,
    MAP,
    SEQUENCE
  };

  class Node;

  using NodePtr = std::shared_ptr<Node>;

  template <typename ...Args>
  NodePtr makeNode(Args &&... args) {
    return std::make_shared<Node>(std::forward<Args>(args)...);
  }

  class Node {
  public:
    struct Undefined {};
    struct Null {};
    using Scalar = std::string;
    using Map = std::unordered_map<NodePtr, NodePtr>;
    using Sequence = std::vector<NodePtr>;
  
    Node() = default;
    Node(const Node &) = default;
    Node(Node &&) = default;
    Node &operator=(const Node &) = default;
    Node &operator=(Node &&) = default;
    ~Node() = default;
    
    explicit Node(NodeType);
    
    NodeType type() const;
    
    Scalar &scalar();
    const Scalar &scalar() const;
    Map &map();
    const Map &map() const;
    Sequence &sequence();
    const Sequence &sequence() const;
    
    NodePtr deepCopy() const;
    
  private:
    boost::variant<
      Undefined,
      Null,
      Scalar,
      Map,
      Sequence
    > data;
  };
}

#endif

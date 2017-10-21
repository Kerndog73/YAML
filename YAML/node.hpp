//
//  node.hpp
//  YAML
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <boost/variant.hpp>
#include <boost/unordered_map.hpp>
#include <vector>
#include <string>

namespace YAML {
  class Node;

  class Node {
  public:
    struct Undefined {};
    using Scalar = std::string;
    using Map = boost::unordered_map<Node, Node>;
    using Sequence = std::vector<Node>;
  
    Node() = default;

  private:
    boost::variant<
      Undefined,
      Scalar,
      Map,
      Sequence
    > data;
  };
}

#endif

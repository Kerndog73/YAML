//
//  node.cpp
//  YAML
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "node.hpp"

using namespace YAML;

Node::Node(const NodeType type) {
  switch (type) {
    case NodeType::UNDEFINED:
      data = Undefined();
      break;
    case NodeType::NUL:
      data = Null();
      break;
    case NodeType::SCALAR:
      data = Scalar();
      break;
    case NodeType::MAP:
      data = Map();
      break;
    case NodeType::SEQUENCE:
      data = Sequence();
      break;
  }
}


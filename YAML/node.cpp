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

NodeType Node::type() const {
  return static_cast<NodeType>(data.which());
}

Node::Scalar &Node::scalar() {
  return boost::get<Scalar>(data);
}

const Node::Scalar &Node::scalar() const {
  return boost::get<Scalar>(data);
}

Node::Map &Node::map() {
  return boost::get<Map>(data);
}

const Node::Map &Node::map() const {
  return boost::get<Map>(data);
}

Node::Sequence &Node::sequence() {
  return boost::get<Sequence>(data);
}

const Node::Sequence &Node::sequence() const {
  return boost::get<Sequence>(data);
}

NodePtr Node::deepCopy() const {
  const NodeType nodeType = type();
  const NodePtr node = makeNode(nodeType);
  
  if (nodeType == NodeType::SCALAR) {
    boost::get<Scalar>(node->data) = boost::get<Scalar>(data);
  } else if (nodeType == NodeType::MAP) {
    const auto &src = boost::get<Map>(data);
    auto &dst = boost::get<Map>(node->data);
    for (auto n = src.cbegin(); n != src.cend(); ++n) {
      dst.emplace(n->first->deepCopy(), n->second->deepCopy());
    }
  } else if (nodeType == NodeType::SEQUENCE) {
    const auto &src = boost::get<Sequence>(data);
    auto &dst = boost::get<Sequence>(node->data);
    for (auto n = src.cbegin(); n != src.cend(); ++n) {
      dst.emplace_back((*n)->deepCopy());
    }
  }
  
  return node;
}

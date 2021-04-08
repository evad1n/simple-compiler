#include "base.h"
#include "../symbol.h"

Node::~Node() {}

StartNode::StartNode(ProgramNode* pn)
    : programNode(pn) {}
void StartNode::Code(InstructionsClass& machineCode) {
    this->programNode->Code(machineCode);
}
StartNode::~StartNode() {
    delete this->programNode;
}
void StartNode::Interpret() {
    this->programNode->Interpret();
}

ProgramNode::ProgramNode(BlockNode* bn)
    : blockNode(bn) {}
void ProgramNode::Code(InstructionsClass& machineCode) {
    this->blockNode->Code(machineCode);
}
ProgramNode::~ProgramNode() {
    delete this->blockNode;
}
void ProgramNode::Interpret() {
    this->blockNode->Interpret();
}

BlockNode::BlockNode(StatementGroupNode* sgn)
    : sgNode(sgn) {}
BlockNode::~BlockNode() {
    delete this->sgNode;
}
void BlockNode::Interpret() {
    this->sgNode->Interpret();
}

StatementGroupNode::StatementGroupNode()
    : nodes(std::vector<StatementNode*>{}) {}
StatementGroupNode::~StatementGroupNode() {
    for (auto n : this->nodes) {
        delete n;
    }
}
void StatementGroupNode::Interpret() {
    for (auto n : this->nodes) {
        n->Interpret();
    }
}
void StatementGroupNode::AddStatement(StatementNode* node) {
    this->nodes.push_back(node);
}
#if !defined(BASE_H)
#define BASE_H

#include <vector>

class Node;
class StartNode;
class ProgramNode;
class StatementNode;
class BlockNode;
class StatementGroupNode;

class Node {
public:
    virtual ~Node();
    virtual void Interpret() = 0;
};

class StartNode : public Node {
private:
    ProgramNode* programNode;
public:
    StartNode(ProgramNode* pn);
    ~StartNode();

    void Interpret();
};

class ProgramNode : public Node {
private:
    BlockNode* blockNode;
public:
    ProgramNode(BlockNode* bn);
    ~ProgramNode();

    void Interpret();
};

class StatementNode : public Node {
private:

public:
};

class BlockNode : public StatementNode {
private:
    StatementGroupNode* sgNode;
public:
    BlockNode(StatementGroupNode* sgn);
    ~BlockNode();

    void Interpret();
};

class StatementGroupNode : public Node {
private:
    std::vector<StatementNode*> nodes;
public:
    StatementGroupNode();
    ~StatementGroupNode();

    void Interpret();
    void AddStatement(StatementNode* node);
};

#endif // BASE_H

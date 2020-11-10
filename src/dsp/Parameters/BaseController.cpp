#include "BaseController.h"
#include "../../NodeManager.h"

BaseController::BaseController (AudioProcessorValueTreeState& vts,
                                std::array<InputNode, 2>* nodes,
                                StringArray paramsToListenFor) :
    vts (vts),
    nodes (nodes),
    paramsToListenFor (paramsToListenFor)
{
    for (auto& node : *nodes)
    {
        node.addNodeListener (this);
        NodeManager::doForNodes (&node, [=] (DelayNode* n) { n->addNodeListener (this); });
    }

    for (const auto& param : paramsToListenFor)
        vts.addParameterListener (param, this);
}

BaseController::~BaseController()
{
    for (auto& node : *nodes)
        NodeManager::doForNodes (&node, [=] (DelayNode* n) { n->removeNodeListener (this); });

    for (const auto& param : paramsToListenFor)
        vts.removeParameterListener (param, this);
}

void BaseController::nodeAdded (DelayNode* newNode)
{
    newNode->addNodeListener (this);
    newNodeAdded (newNode);
}

void BaseController::nodeRemoved (DelayNode* nodeToRemove)
{
    nodeToRemove->removeNodeListener (this);
}

void BaseController::doForNodes (std::function<void(DelayNode*)> nodeFunc)
{
    for (auto& node : *nodes)
        NodeManager::doForNodes (&node, nodeFunc);
}

/*
 * Node.h
 *
 * Created: 30.06.2017 23:34:39
 *  Author: tabr
 */ 


#ifndef NODE_H_
#define NODE_H_

#include "typedefs.h"

class Node
	{
	public:
		const static uint8_t MAX_NODES	= 255;
		Node* AddNode(Node* newNode)
			{
			Node* emptyNode	= this;
			for (uint8_t i=0;i<MAX_NODES;i++)
				{
				if (emptyNode->IsNextNodeIsEmpty())
					{
					emptyNode->SetNextNode(newNode);
					return emptyNode;
					}
				emptyNode	= emptyNode->GetNextNode();
				}
			return NULL;
			}
		void SetNextNode(Node* newNode)
			{
			this->NextNode	= newNode;
			}
		Node* GetNextNode(void)
			{
			return this->NextNode;
			}
		bool IsNextNodeIsEmpty(void)
			{
			return (this->NextNode == NULL);
			}
	protected:
	private:
		Node* NextNode	= NULL;
	};
class NodeExtended : public Node //should be implemented ONLY GetID()
	{
	public:
		virtual NodeProcessorID_t GetID(void)	= 0;
		NodeExtended* GetNextNode(void)
			{
			return static_cast<NodeExtended*>(Node::GetNextNode());
			}
	protected:
	private:
	};

class NodeProcessor
	{
	public:
		NodeExtended* GetNode(NodeProcessorID_t ID)
			{
			NodeExtended* I	= this->GetContainer();
			for (uint8_t i=0;i<Node::MAX_NODES;i++)
				{
				if (I->GetID() == ID)
					{
					return I;
					}
				//I	= static_cast<NodeProcessor*>(I->GetNextNode());
				I	= I->GetNextNode();
				if (I == NULL)
					{
					break;
					}
				}
			return this->GetContainer();
			}
	protected:
	private:
		virtual NodeExtended* GetContainer(void)		= 0;
	};
/*
template <class C>
class NodeProcessorT
  {
  public:
  C* GetNode(NodeProcessorID_t ID)
    {
    C* I	= this->GetContainer();
    for (uint8_t i=0;i<Node::MAX_NODES;i++)
      {
      if (I->GetID() == ID)
        {
        return I;
        }
      //I	= static_cast<NodeProcessor*>(I->GetNextNode());
      I	= static_cast<C*>(I->GetNextNode());
      if (I == NULL)
        {
        break;
        }
      }
    return this->GetContainer();
    }
  C* Get(void)
    {
    return static_cast<C*>(&this);
    }
  protected:
  private:
  virtual C* GetContainer(void)		= 0;
  };
*/
template <class C>
class NodeProcessorT
  {
  public:
  bool IsIdExists(NodeProcessorID_t ID)
    {
    return (this->GetNode(ID) != NULL);//NULL mean not exists
    }
  C* GetNode(NodeProcessorID_t ID)
    {
    C* I	= this->GetContainer();
    for (uint8_t i=0;i<Node::MAX_NODES;i++)
      {
      if (I->GetID() == ID)
        {
        return I;
        }
      //I	= static_cast<NodeProcessor*>(I->GetNextNode());
      I	= static_cast<C*>(I->GetNextNode());
      if (I == NULL)
        {
        break;
        }
      }
    return this->GetContainer();
    }
  C* Get(void)
    {
    return static_cast<C*>(&this);
    }
  bool RegisterNew(C* NewNode)
    {
    Node* ResultNode  = this->Container.AddNode(NewNode);
    if (ResultNode == NULL)
      {
      return false;
      }
    this->regiserted_counter++;
    return true;
    }
  NodeProcessorID_t GetRegisteredNodeNum(void)
    {
    return this->regiserted_counter;
    }
  C* GetContainer(void)
    {
    return &this->Container;
    }
  protected:
  private:
    C Container;
    NodeProcessorID_t regiserted_counter=0;
  };
#endif /* NODE_H_ */
#include "variable.h"

Node::~Node() {}

Variable::Variable() {}
Variable::~Variable() {}

Variable::Variable(int _id, string _name, double _value){
	id = _id;
	name = _name;
	value = _value;
	derivative = 0;
}

void Variable::setFrom(Function *_from) {
	from = _from;
}

void Variable::addTo(Function *_to) {
	to.push_back(_to);
}

vector<Node *> Variable::getIncomings() {
	vector<Node *> incomings;
    if(from != nullptr)
        incomings.push_back((Node *) from);
	return incomings;
}

vector<Node *> Variable::getOutgoings() {
    vector<Node *> outgoings;
    for(int i=0, n=to.size(); i<n; i++)
        if(to[i] != nullptr)
            outgoings.push_back((Node *) to[i]);

	return  outgoings;
}



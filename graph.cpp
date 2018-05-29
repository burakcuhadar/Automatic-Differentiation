#include "graph.h"

using namespace std;

// helper function that checks whether the given string is number or not.
bool isNumber(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

//helper function that splits an input line into words
template <class Container>
void split(const std::string& str, Container& cont)
{
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(cont));
}

int Graph::getVariable(string inp){
    int res;
    if( isNumber(inp) ){
        double val = stod(inp.c_str());
        idCount++;
        name[idCount] = inp;
        vars[idCount] = new Variable(idCount, inp, val);
        res = idCount;
        type[idCount] = VARIABLE;
    }
    else{
        if(id.find(inp)==id.end()){
            idCount++;
            id[inp] = idCount;
            name[idCount] = inp;
            vars[idCount] = new Variable(idCount, inp);
            res = idCount;
            type[idCount] = VARIABLE;
        }
        else{
            res = id[inp];
        }
    }
    // printf("%s -> %d\n",inp.c_str(), res);
    return res;
}

int Graph::getFunction(string fnc){
    idCount++;
    name[idCount] = fnc;
    type[idCount] = FUNCTION;
    Function *f;
    // cout << "new Function: " << fnc << endl;
    if(fnc.compare("mult")==0)
        f = new Multiplication(idCount, fnc);
    else if(fnc.compare("add")==0)
        f = new Addition(idCount, fnc);
    else if(fnc.compare("subs")==0)
        f = new Subtraction(idCount, fnc);
    else if(fnc.compare("divide")==0)
        f = new Division(idCount, fnc);
    else if(fnc.compare("sin")==0)
        f = new Sine(idCount, fnc);
    else if(fnc.compare("cos")==0)
        f = new Cosine(idCount, fnc);
    else if(fnc.compare("identity")==0)
        f = new Identity(idCount, fnc);
    else if(fnc.compare("tan")==0)
        f = new Tangent(idCount, fnc);
    else if(fnc.compare("acos")==0)
        f = new ArcCosine(idCount, fnc);
    else if(fnc.compare("asin")==0)
        f = new ArcSine(idCount, fnc);
    else if(fnc.compare("atan")==0)
        f = new ArcTangent(idCount, fnc);
    else if(fnc.compare("exp")==0)
        f = new Exponential(idCount, fnc);
    else if(fnc.compare("log")==0)
        f = new Log(idCount, fnc);
    else if(fnc.compare("log10")==0)
        f = new Log10(idCount, fnc);
    else if(fnc.compare("pow")==0)
        f = new Power(idCount, fnc);
    else if(fnc.compare("sqrt")==0)
        f = new Sqrt(idCount, fnc);
    fncs[idCount] = f;
    return idCount;
}

void Graph::addUnaryFunction(string fnc, string inp, string out){

    int fId = getFunction(fnc);
    int inpId = getVariable(inp);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addBinaryFunction(string fnc, string inp1, string inp2, string out){
    int fId = getFunction(fnc);
    int inpId1 = getVariable(inp1);
    int inpId2 = getVariable(inp2);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId1]);
    fncs[fId]->addInput(vars[inpId2]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId1]->addTo(fncs[fId]);
    vars[inpId2]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addAssignment(string lvalue, string rvalue) {
    addUnaryFunction("identity", rvalue, lvalue);
}

void Graph::readGraph(string fileName){
    ifstream infile(fileName);
    string line;
    //process the lines until the end of file is reached
    while(getline(infile, line)){
        vector<string> words;
        split(line, words);
        //if there are two words in the line, either input or output definition
        if(words.size() == 2){
            if(words[0].compare("input") == 0)
                inputNodes.push_back( getVariable(words[1]) );
            else if( words[0].compare("output") == 0 )
                outputNode = getVariable(words[1]);
            else
                cout <<"Wrong input file format!" << endl;
        }
        //if there are three words in the line it means an assigment is added to the graph
        else if( words.size() == 3 ){
            addAssignment(words[0], words[2]);
        }
        //if there are four words in the line it means a unary function is added to the graph
        else if(words.size() == 4){
            addUnaryFunction(words[2], words[3], words[0]);
        }
        //if there are five words in the line it means a binary function is added to the graph
        else if(words.size() == 5){
            addBinaryFunction(words[2], words[3], words[4] ,words[0]);
        }else{
            cout <<"Wrong input file format!" << endl;
        }
    }
    //if end of file is not reached there is error while reading
    if( !infile.eof() )
        cout << "Error reading the file!" << endl;
    infile.close();
}

void Graph::initTopologicalOrder(){
	//stores number of visited nodes
	int visited_nodes = 0;
    //stores in-degrees of nodes
    vector<int> in_degree(idCount,0);
    //fill in-degrees
    for(unordered_map<int, Variable*>::iterator itr = vars.begin(); itr != vars.end(); itr++){
        in_degree[itr->first-1] = itr->second->getIncomings().size();
    }
    for(unordered_map<int, Function*>::iterator itr = fncs.begin(); itr != fncs.end(); itr++){
        in_degree[itr->first-1] = itr->second->getIncomings().size();
    }
    //queue for ids of nodes that have in-degree 0
    queue<int> q;
    for(int i=0; i<idCount; i++){
        if(in_degree[i]==0)
            q.push(i);
    }
    //process queue
    while(!q.empty()){
        int curr_node = q.front();
        q.pop();
        topological_order.push_back(curr_node+1);
        //decrease in-degree of the neighbors of curr_node by 1
        vector<Node*> curr_neighbors;
        if(type[curr_node+1] == VARIABLE)
             curr_neighbors = vars[curr_node+1]->getOutgoings();
        else
            curr_neighbors = fncs[curr_node+1]->getOutgoings();
        for(int i=0; i<curr_neighbors.size(); i++)
            //if in-degree becomes 0 push it to the queue
            if(--in_degree[curr_neighbors[i]->id-1] == 0)
                q.push(curr_neighbors[i]->id-1);
        visited_nodes++;
    }
    isCyclic = visited_nodes != idCount;
}

double Graph::forwardPass(vector<double> inputValues){
    for(int i=0; i< inputNodes.size(); i++){
        vars[inputNodes[i]]->value = inputValues[i];
    }
    for(int i=0; i<topological_order.size(); i++){
        if(type[topological_order[i]] == FUNCTION)
            fncs[topological_order[i]]->doForward();
    }
    return vars[outputNode]->value;
}

vector<double> Graph::backwardPass(){
	//reset derivative values of variables 
	for(unordered_map<int, Variable*>::iterator itr = vars.begin(); itr != vars.end(); itr++){
        itr->second->derivative = 0;
    }
    vars[outputNode]->derivative = 1.0;
    for(int i=topological_order.size()-1; i>=0; i--){
        if(type[topological_order[i]] == FUNCTION)
            fncs[topological_order[i]]->doBackward();
    }
    vector<double> derivatives;
    for(int i=0; i<inputNodes.size(); i++){
    	derivatives.push_back(vars[inputNodes[i]]->derivative);
    }
    return derivatives;
}

string Graph::getOutputName(){
    return name[outputNode];
}

string Graph::getDerivativeName(){
    stringstream ss;
    for(int i=0; i<inputNodes.size(); i++){
    	ss << "d" << name[outputNode] << "/d" << name[inputNodes[i]] << " "; 
    }
    return ss.str();
}

Graph::~Graph() {}
#include "graph.h"
#include <iomanip>


//helper function that splits an input line into words
template <class Container>
void split(const std::string& str, Container& cont)
{
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(cont));
}

int main(int argc, char *argv[]) {
	if(argc != 5){
		cout << "Run the code with the following command: ./project4 [expr_file] [input_file] [result_file] [derivative_file] " << endl;
        return 1;
	}
	//Create graph for computation
	Graph myGraph;
	//construct graph from the given file
	myGraph.readGraph(argv[1]);
	//read input values from the input file
	ifstream infile(argv[2]);
    //output file to write forward pass values
    ofstream result;
    result.open(argv[3]);
    //output file to write backward pass values
    ofstream derivative;
    derivative.open(argv[4]);
    myGraph.initTopologicalOrder();
    //if there is cycle in the graph print error message to output files
    if(myGraph.isCyclic){
    	result << "ERROR: COMPUTATION GRAPH HAS CYCLE!" << endl;
    	derivative << "ERROR: COMPUTATION GRAPH HAS CYCLE!" << endl;
    	return -1;
    }
    result << myGraph.getOutputName() << endl;
    derivative << myGraph.getDerivativeName() << endl;
    string line;
    getline(infile, line);
    //process lines until the end of file is reached
    while(getline(infile, line)){
    	//stores input values that has been read from the input file
		vector<double> inputValues;
		vector<string> words;
		split(line, words);
		for(int i=0; i<words.size(); i++)
			inputValues.push_back(stod(words[i]));
		result << setprecision(17) << myGraph.forwardPass(inputValues) << endl;
		vector<double> derivatives = myGraph.backwardPass();
		for(int i=0; i<derivatives.size(); i++){
			derivative << setprecision(17) << derivatives[i] << " ";
		}
		derivative << endl;
    }
	
	return 0;
}

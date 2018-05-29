#include <math.h>
#include "function.h"

Function::Function() {}
Function::~Function() {}

Function::Function(int _id, string _name) {
    id = _id;
    name = _name;
}

void Function::addInput(Variable *input){
    inputs.push_back(input);
}

void Function::setOutput(Variable *_output) {
    output = _output;
}

vector<Node *> Function::getIncomings() {
    vector<Node *> incomings;
    for(int i=0, n=inputs.size(); i<n; i++){
        if(inputs[i] != nullptr)
            incomings.push_back((Node *) inputs[i]);
    }
    return incomings;
}

vector<Node *> Function::getOutgoings() {
    vector<Node *> outgoings;
    if(output != nullptr)
        outgoings.push_back((Node *) output);
    return outgoings;
}

Multiplication::Multiplication(int _id, string _name){
	id = _id;
	name = _name;
}

void Multiplication::doForward() {
    output->value = inputs[0]->value * inputs[1]->value;
}

void Multiplication::doBackward() {
	inputs[0]->derivative += inputs[1]->value * output->derivative;
	inputs[1]->derivative += inputs[0]->value * output->derivative;
}

Addition::Addition(int _id, string _name){
	id = _id;
	name = _name;
}

void Addition::doForward() {
    output->value = inputs[0]->value + inputs[1]->value;
}

void Addition::doBackward() {
	inputs[0]->derivative += output->derivative;
	inputs[1]->derivative += output->derivative;
}

Division::Division(int _id, string _name){
	id = _id;
	name = _name;
}

void Division::doForward() {
    output->value = inputs[0]->value / inputs[1]->value;
}

void Division::doBackward() {
	inputs[0]->derivative += output->derivative / inputs[1]->value;
	inputs[1]->derivative += output->derivative * -1.0 * inputs[0]->value / pow(inputs[1]->value, 2);
}

Subtraction::Subtraction(int _id, string _name){
	id = _id;
	name = _name;
}

void Subtraction::doForward() {
    output->value = inputs[0]->value - inputs[1]->value;
}

void Subtraction::doBackward() {
	inputs[0]->derivative += output->derivative;
	inputs[1]->derivative += -1.0 * output->derivative;
}

Sine::Sine(int _id, string _name){
	id = _id;
	name = _name;
}

void Sine::doForward() {
	output->value =sin(inputs[0]->value);
}

void Sine::doBackward() {
	inputs[0]->derivative += output->derivative * cos(inputs[0]->value);
}

Cosine::Cosine(int _id, string _name){
	id = _id;
	name = _name;
}

void Cosine::doForward() {
	output->value =cos(inputs[0]->value);
}

void Cosine::doBackward() {
	inputs[0]->derivative += output->derivative * -1.0 *sin(inputs[0]->value);	
}

Identity::Identity(int _id, string _name){
	id = _id;
	name = _name;
}

void Identity::doForward() {
    output->value = inputs[0]->value;
}

void Identity::doBackward() {
	inputs[0]->derivative += output->derivative;
}

Tangent::Tangent(int _id, string _name){
	id = _id;
	name = _name;
}

void Tangent::doForward() {
	output->value =tan(inputs[0]->value);
}

void Tangent::doBackward() {
	inputs[0]->derivative += output->derivative * 1.0 / pow( cos(inputs[0]->value) ,2 );	
}

ArcCosine::ArcCosine(int _id, string _name){
	id = _id;
	name = _name;
}

void ArcCosine::doForward() {
	output->value = acos(inputs[0]->value);
}

void ArcCosine::doBackward() {
	inputs[0]->derivative += output->derivative * -1.0 / sqrt(1 - pow(inputs[0]->value,2));
}

ArcTangent::ArcTangent(int _id, string _name){
	id = _id;
	name = _name;
}

void ArcTangent::doForward() {
	output->value = atan(inputs[0]->value);
}

void ArcTangent::doBackward() {
	inputs[0]->derivative += output->derivative * 1.0 / (1 + pow(inputs[0]->value,2));
}

ArcSine::ArcSine(int _id, string _name){
	id = _id;
	name = _name;
}

void ArcSine::doForward() {
	output->value = asin(inputs[0]->value);
}

void ArcSine::doBackward() {
	inputs[0]->derivative += output->derivative * 1.0 / sqrt(1 - pow(inputs[0]->value,2));
}

Exponential::Exponential(int _id, string _name){
	id = _id;
	name = _name;
}

void Exponential::doForward() {
	output->value = exp(inputs[0]->value);
}

void Exponential::doBackward() {
	inputs[0]->derivative += output->derivative * exp(inputs[0]->value);
}

Log::Log(int _id, string _name){
	id = _id;
	name = _name;
}

void Log::doForward() {
	output->value = log(inputs[0]->value);	
}

void Log::doBackward() {
	inputs[0]->derivative += output->derivative / inputs[0]->value;
}

Log10::Log10(int _id, string _name){
	id = _id;
	name = _name;
}

void Log10::doForward() {
	output->value = log10(inputs[0]->value);
}

void Log10::doBackward() {
	inputs[0]->derivative += output->derivative / (inputs[0]->value * log(10));
}

Power::Power(int _id, string _name){
	id = _id;
	name = _name;
}

void Power::doForward() {
	output->value = pow(inputs[0]->value, inputs[1]->value);
}

void Power::doBackward() {
	inputs[0]->derivative += output->derivative * inputs[1]->value * pow( inputs[0]->value, inputs[1]->value - 1.0);
	inputs[1]->derivative += output->derivative * log(inputs[0]->value) * pow(inputs[0]->value, inputs[1]->value);
}

Sqrt::Sqrt(int _id, string _name){
	id = _id;
	name = _name;
}

void Sqrt::doForward() {
	output->value = sqrt(inputs[0]->value);
}

void Sqrt::doBackward() {
	inputs[0]->derivative += output->derivative * 0.5 / sqrt(inputs[0]->value);
}










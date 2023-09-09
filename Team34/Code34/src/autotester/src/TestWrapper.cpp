#include "TestWrapper.h"
#include "FileReader.h"
#include "sp/SourceProcessor.h"
#include "qps/QPS.h"

#include <fstream>
#include <iostream>


// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
    if (wrapper == 0) wrapper = new TestWrapper;
    return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
    // create any objects here as instance variables of this class
    // as well as any initialization required for your spa program
    pkb = new PKB(di);
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
    // tokenizing file contents
    std::string fileContents = FileReader::readFile(filename);
    SourceProcessor sp;
    sp.parse(fileContents, di);
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results) {
    // call your evaluator to evaluate the query here
    // ...code to evaluate query...
    QPS qps;
    results = qps.process(query, di);
    // store the answers to the query in the results list (it is initially empty)
    // each result must be a std::string.
}

#include "Relation.cpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    try{
        Relation relat_test1 = Relation("data/facebook.dat");
        Relation relat_test2 = Relation("data/facebook.dat");
        vector<int> ens1;
        vector<int> ens2;
        ens1.push_back(0);
        ens2.push_back(1);
        Relation relat_test = Relation(relat_test1,relat_test2,ens1,ens2);
        int size = relat_test.getSize();
        for(int i=0;i<size;i++){
            for(int j=0;j<relat_test.getArity();j++){
                std::cout<<relat_test.getOrderedTuple(i)[j]<<", ";
            }
            cout<<endl;
        }
    }
    catch(string const& err){
        cout<<err<<endl;
    }
}



#include "Relation.cpp"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    try{
        Relation relat_test = Relation("data/facebook.dat");
        int size = relat_test.getSize();
        int perm[2] = {1,0};
        relat_test.reorder(perm);
        for(int i=0;i<size;i++){
            for(int j=0;j<relat_test.getArity();j++){
                cout<<relat_test.getOrderedTuple(i)[j]<<", ";
            }
            cout<<endl;
        }
    }
    catch(string const& err){
        cout<<err<<endl;
    }
}

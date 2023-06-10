#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;
class Detail
{
protected:
    Detail() = default;
    virtual ~Detail() = default;
};
class Assembly : public Detail
{
protected:
    friend void FillVector(vector<Assembly>* vec); 
    explicit Assembly(const string& detail_info) : detail(detail_info) {
        cout << "Assembly constructor is called." << endl;
    }
    const string& getDetail() const { 
        return detail;
    }
private:
    string detail;
};
void FillVector(vector<Assembly>* vec) { 
    for (int i = 0; i < 5; ++i)
    {
        auto a = unique_ptr<Assembly>(new Assembly("Detail #" + to_string(i)));
        vec->push_back(move(*a));
    }
}
vector<Assembly> vec;
int main() {
    FillVector(&vec);
    for (auto i = vec.begin(); i != vec.end(); i++)
    {
        cout << i->getDetail() << endl; 
    }
    return 0;
}
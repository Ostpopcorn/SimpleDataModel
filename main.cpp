#include <iostream>
#include <string>
#include "include/DataModel.h"
struct hej{

};
int main() {
    std::cout << "Hello, World!" << std::endl;
    DataModel<int,int,std::string> model{};
    // auto& a = model.data;
    // Do it with pointer to ensure no exceptions are called.
    // std::cout << std::holds_alternative<int>(a) << std::endl;
    // std::cout << std::holds_alternative<std::string>(a) << std::endl;

    using namespace std::string_literals;

    int i = 3;
    std::string s = "string";
    model.set_entry(1,i);
    model.set_entry(2,std::move(s));
    std::cout << (true?"true":"false") << std::endl;
    std::cout << model.get_entry(2)->value_has_changed() << std::endl;
    std::cout << model.get_entry(2)->value_has_changed() << std::endl;
    model.set_entry(2,"string"s);
    std::cout << model.get_entry(2)->value_has_changed() << std::endl;
    model.set_entry(2,"hejhej"s);
    std::cout << model.get_entry(2)->value_has_changed() << std::endl;
    // a[1] = DataModelEntry<int,std::string>(i);
    // a[2] = DataModelEntry<int,std::string>(s);

    return 0;
}

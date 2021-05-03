#ifndef DATA_MODEL_DATAMODEL_H
#define DATA_MODEL_DATAMODEL_H

#include <variant>
#include <map>
#include "DataModelEntry.h"

template<typename identifier_type,typename... object_types>
class DataModel {
public:
    template<typename return_object_types>
    return_object_types* get_entry_object(identifier_type identifier);

    DataModelEntry<object_types...>* get_entry(identifier_type identifier);

    template<typename set_object_types>
    void set_entry(identifier_type identifier,set_object_types && new_obj);
private:
    std::map<identifier_type,DataModelEntry<object_types...>> data{};
};

template<typename identifier_type, typename... object_types>
template<typename return_object_types>
return_object_types* DataModel<identifier_type, object_types...>::get_entry_object(identifier_type identifier) {
    return &(get_entry()->template get<return_object_types>());
}

template<typename identifier_type, typename... object_types>
template<typename set_object_types>
void DataModel<identifier_type, object_types...>::set_entry(identifier_type identifier, set_object_types && new_obj) {
    get_entry(identifier)->template set(std::forward<set_object_types>(new_obj));
}

template<typename identifier_type, typename... object_types>
DataModelEntry<object_types...> *DataModel<identifier_type, object_types...>::get_entry(identifier_type identifier) {
    return &(data[identifier]);
}


#endif //DATA_MODEL_DATAMODEL_H

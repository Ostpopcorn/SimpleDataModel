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
    void set_entry(identifier_type identifier,set_object_types && new_obj,bool set_has_changed_on_equality = false);
private:
    std::map<identifier_type,DataModelEntry<object_types...>> data{};
};

#include "DataModel.tpp"

#endif //DATA_MODEL_DATAMODEL_H

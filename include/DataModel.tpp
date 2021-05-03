//
// Created by adrian on 2021-04-29.
//



template<typename identifier_type, typename... object_types>
template<typename return_object_types>
return_object_types* DataModel<identifier_type, object_types...>::get_entry_object(identifier_type identifier) {
    return get_entry(identifier)->template get<return_object_types>();
}

template<typename identifier_type, typename... object_types>
template<typename set_object_types>
void DataModel<identifier_type, object_types...>::set_entry(identifier_type identifier, set_object_types && new_obj,bool set_has_changed_on_equality) {
    get_entry(identifier)->template set(std::forward<set_object_types>(new_obj),set_has_changed_on_equality);
}

template<typename identifier_type, typename... object_types>
DataModelEntry<object_types...> *DataModel<identifier_type, object_types...>::get_entry(identifier_type identifier) {
    return &(data[identifier]);
}

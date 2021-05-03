//
// Created by adrian on 2021-04-29.
//


template<typename... object_types>
bool DataModelEntry<object_types...>::value_has_changed(bool reset) {
    bool return_val{has_changed};
    if (reset) {
        has_changed = false;
    }
    return return_val;
}

template<typename... object_types>
template<typename get_object_type>
get_object_type *DataModelEntry<object_types...>::get() {
    // Kanske göra något med variadic templates här för att kolla om typen finns med i listan.
    if (std::holds_alternative<get_object_type>(data)) {
        return &std::get<get_object_type>(data);
    } else {
        return nullptr;
    };
}

template<typename... object_types>
template<typename set_object_type>
void DataModelEntry<object_types...>::set(set_object_type &&new_obj, bool set_has_changed_on_equality) {

    if (std::holds_alternative<std::decay_t<set_object_type>>(data)) {
        if (set_has_changed_on_equality || (std::get<std::decay_t<set_object_type>>(data) != new_obj)) {
            has_changed = true;
        }
        data = new_obj;
    } else {
        has_changed = true;
        data = new_obj;
    }
}

template<typename... object_types>
template<typename initial_type>
DataModelEntry<object_types...>::DataModelEntry(initial_type &&obj) {
    data = obj;
    has_changed = true;
}

template<typename... object_types>
DataModelEntry<object_types...>::DataModelEntry() {

}

template<typename... object_types>
bool DataModelEntry<object_types...>::operator==(const DataModelEntry<object_types...> &rhs) const {
    return data == rhs.data;
}


template<typename... object_types>
bool DataModelEntry<object_types...>::operator!=(const DataModelEntry<object_types...> &rhs) const {
    return !(*this == rhs);
}

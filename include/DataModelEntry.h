#ifndef DATA_MODEL_DATAMODELENTRY_H
#define DATA_MODEL_DATAMODELENTRY_H

#include <variant>
#include <optional>
#include <type_traits>

template<typename... object_types>
class DataModelEntry {
public:
    DataModelEntry();
    template<typename initial_type>
    DataModelEntry(initial_type &&obj);

    bool value_has_changed(bool reset = true);

    template<typename get_object_type>
    get_object_type * get();

    template<typename set_object_type>
    void set(set_object_type &&new_obj);

    bool operator==(DataModelEntry<object_types...> const & rhs) const;

private:
    std::variant<object_types...> data{};
    bool has_changed{false};
};

template<typename... object_types>
bool DataModelEntry<object_types...>::value_has_changed(bool reset) {
    bool return_val{has_changed};
    if (reset){
        has_changed = false;
    }
    return return_val;
}

template<typename... object_types>
template<typename get_object_type>
get_object_type * DataModelEntry<object_types...>::get() {
    // Kanske göra något med variadic templates här för att kolla om typen finns med i listan.
    if(std::holds_alternative<get_object_type>(data)){
        return & std::get<get_object_type>(data);
    }else{
        return nullptr;
    };
}

template<typename... object_types>
template<typename set_object_type>
void DataModelEntry<object_types...>::set(set_object_type &&new_obj) {

    if(std::holds_alternative<std::decay_t<set_object_type>>(data)){
        if (std::get<std::decay_t<set_object_type>>(data) != new_obj){
            has_changed = true;
        }
        data = new_obj;
    }else{
        has_changed = true;
        data = new_obj;
    }
}

template<typename... object_types>
template<typename initial_type>
DataModelEntry<object_types...>::DataModelEntry(initial_type && obj) {
    data = obj;
    has_changed = true;
}

template<typename... object_types>
DataModelEntry<object_types...>::DataModelEntry() {

}

template<typename... object_types>
bool DataModelEntry<object_types...>::operator==(const DataModelEntry<object_types...> &rhs) const {
    return data = rhs.data;
}


#endif //DATA_MODEL_DATAMODELENTRY_H

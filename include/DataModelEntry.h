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
    get_object_type *get();

    template<typename set_object_type>
    void set(set_object_type &&new_obj, bool set_has_changed_on_equality = false);

    bool operator==(DataModelEntry<object_types...> const &rhs) const;

    bool operator!=(DataModelEntry<object_types...> const &rhs) const;

private:
    std::variant<object_types...> data{};
    bool has_changed{false};
};

#include "DataModelEntry.tpp"

#endif //DATA_MODEL_DATAMODELENTRY_H

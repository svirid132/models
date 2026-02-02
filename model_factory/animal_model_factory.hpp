#pragma once

#include <QAbstractListModel>
#include <domain/animal.hpp>
#include <model/composed_model.hpp>

enum class AnimalRoles {
    TypeRole = Qt::UserRole + 1,
    SizeRole
};

class AnimalModelFactory
{
public:
    AnimalModelFactory();

    static ComposedModel* createModel(QList<Animal> init_animals = {}, QObject* parent = nullptr)
    {
        auto animal_items = std::make_unique<TemplateVectorItems<Animal>>(std::move(init_animals));
        auto animal_items_ptr = animal_items.get();

        auto data_cb = [](const Animal& item, int row, int role) -> QVariant {
            if ((AnimalRoles)role == AnimalRoles::TypeRole)
                return QString::fromStdString(item.type);
            else if ((AnimalRoles)role == AnimalRoles::SizeRole)
                return QString::fromStdString(item.size);

            return QVariant();
        };

        auto role_names_cb = []() -> QHash<int, QByteArray> {
            QHash<int, QByteArray> roles;
            roles[(int)AnimalRoles::TypeRole] = "type";
            roles[(int)AnimalRoles::SizeRole] = "size";

            return roles;
        };

        auto set_data_cb = [animal_items_ptr](int row, const QVariant &value, int role) -> bool
        {
            QList<Animal>& items = animal_items_ptr->getItems();
            if ((AnimalRoles)role == AnimalRoles::SizeRole)
            {
                items[row].size = value.toString().toStdString();
                return true;
            }
            else if ((AnimalRoles)role == AnimalRoles::TypeRole)
            {
                items[row].type = value.toString().toStdString();
                return true;
            }

            return false;
        };

        ComposedModel* vector_model = new ComposedModel(parent);
        animal_items->overrideData(std::move(data_cb));
        animal_items->overrideRoleNames(std::move(role_names_cb));
        animal_items->overrideSetData(std::move(set_data_cb));
        vector_model->setTemplateItems(std::move(animal_items));

        return vector_model;
    }
};

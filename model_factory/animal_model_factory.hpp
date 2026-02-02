#pragma once

#include <domain/animal.hpp>
#include <model/composed_model.hpp>
#include <model/template_items/template_vector_items.hpp>

enum class AnimalRoles {
    TypeRole = Qt::UserRole + 1,
    SizeRole
};

struct AnimalModelSet
{
    using data_changed_cb = std::function<bool(Animal)>;
    using bind_data_changed_cb = std::function<void(data_changed_cb)>;
    using append_cb = std::function<void(const Animal&)>;
    using remove_last_animal_cb = std::function<void()>;

    std::unique_ptr<ComposedModel> animal_model;
    bind_data_changed_cb bind_data_changed;
    append_cb append;
    remove_last_animal_cb remove_last_animal;
};

class AnimalModelFactory
{
    using animal_data_changed_cb = AnimalModelSet::data_changed_cb;
    using animal_data_changed_cbs = std::vector<animal_data_changed_cb>;

public:
    static AnimalModelSet createModel(QList<Animal> init_animals = {}, QObject* parent = nullptr)
    {
        std::shared_ptr<animal_data_changed_cbs> on_animal_data_changeds = std::make_shared<animal_data_changed_cbs>();

        auto animal_items = std::make_unique<TemplateVectorItems<Animal>>(std::move(init_animals));
        auto animal_items_ptr = animal_items.get();

        auto bind_data_changed = [on_animal_data_changeds] (animal_data_changed_cb cb)
        {
            on_animal_data_changeds->push_back(std::move(cb));
        };

        auto data_cb = [on_animal_data_changeds](const Animal& item, int row, int role) -> QVariant
        {
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


        auto set_data_cb = [animal_items_ptr, on_animal_data_changeds](int row, const QVariant &value, int role) -> bool
        {
            QList<Animal>& items = animal_items_ptr->getItems();
            if ((AnimalRoles)role == AnimalRoles::SizeRole)
            {
                items[row].size = value.toString().toStdString();

                for (auto &cb : *on_animal_data_changeds)
                {
                    cb(items[row]);
                }

                return true;
            }
            else if ((AnimalRoles)role == AnimalRoles::TypeRole)
            {
                items[row].type = value.toString().toStdString();

                for (auto &cb : *on_animal_data_changeds)
                {
                    cb(items[row]);
                }

                return true;
            }

            return false;
        };

        auto animal_model = std::make_unique<ComposedModel>(parent);
        auto animal_model_ptr = animal_model.get();
        animal_items->overrideData(std::move(data_cb));
        animal_items->overrideRoleNames(std::move(role_names_cb));
        animal_items->overrideSetData(std::move(set_data_cb));
        animal_model->setTemplateItems(std::move(animal_items));

        auto append_cb = [animal_items_ptr, animal_model_ptr](const Animal& animal)
        {
            QList<Animal>& items = animal_items_ptr->getItems();
            animal_model_ptr->beginInsertRows(animal_items_ptr->rowCount(), animal_items_ptr->rowCount());
            items.push_back(animal);
            animal_model_ptr->endInsertRows();
        };

        auto remove_last_animal = [animal_items_ptr, animal_model_ptr]()
        {
            if (animal_items_ptr->rowCount() == 0)
            {
                return;
            }
            QList<Animal>& items = animal_items_ptr->getItems();
            int last_index = animal_items_ptr->rowCount() - 1;
            animal_model_ptr->beginRemoveRows(last_index, last_index);
            items.removeLast();
            animal_model_ptr->endRemoveRows();
        };

        return  {
            std::move(animal_model),
            std::move(bind_data_changed),
            std::move(append_cb),
            std::move(remove_last_animal)
        };
    }
};

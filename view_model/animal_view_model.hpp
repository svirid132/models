#pragma once

#include <QAbstractItemModel>
#include <QObject>
#include <qqml.h>
#include <model_factory/animal_model_factory.hpp>

class AnimalViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel* animalModel READ animalModel CONSTANT)
public:
    AnimalViewModel(QObject* parent = nullptr) : QObject(parent)
    {
        QList<Animal> init_animals = {
            {"fox", "123"},
            {"qwerty", "asd"},
            {"zxcv", "ghj"}
        };
        animal_model_set_ = AnimalModelFactory::createModel(std::move(init_animals), this);
        animal_model_set_.bind_data_changed([](Animal animal) -> bool
        {
            return true;
        });
    };

    static void registerTypes()
    {
        qmlRegisterUncreatableType<AnimalViewModel>("ViewModel", 1, 0, "AnimalViewModel", "only value type");
    };

    Q_INVOKABLE void appendAnimal()
    {
        animal_model_set_.append({"psevdo_fox", "psevdo_fox"});
    }

    Q_INVOKABLE void removeLastAnimal()
    {
        animal_model_set_.remove_last_animal();
    }

    QAbstractListModel* animalModel()
    {
        return animal_model_set_.animal_model.get();
    }

private:
    AnimalModelSet animal_model_set_;
};

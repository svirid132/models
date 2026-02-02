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
        animal_model_ = AnimalModelFactory::createModel(std::move(init_animals), this);
    };

    static void registerTypes()
    {
        qmlRegisterUncreatableType<AnimalViewModel>("ViewModel", 1, 0, "AnimalViewModel", "only value type");
    };

    QAbstractListModel* animalModel()
    {
        return animal_model_;
    }

private:
    ComposedModel* animal_model_;
};

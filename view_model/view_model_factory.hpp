#pragma once

#include <QObject>
#include <view_model/animal_view_model.hpp>

class ViewModelFactory : public QObject {
    Q_OBJECT
public:
    ViewModelFactory(QObject* parent = nullptr)
        : QObject(parent)
    {}

    Q_INVOKABLE QObject* createAnimalModelView()
    {
        return new AnimalViewModel(this);
    }
};

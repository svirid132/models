#pragma once

#include <view_model/factory/view_model_factory.hpp>
#include <QGuiApplication>
#include <qqml.h>

class ModelsApplication : public QGuiApplication {
    using QGuiApplication::QGuiApplication;

public:
    void registerTypes() {
        // model

        // viewModel
        AnimalViewModel::registerTypes();
    };
    void initModelFactory() {
        ViewModelFactory* view_model_factory = new ViewModelFactory(this);

        qmlRegisterSingletonInstance("ViewModelFactory", 1, 0, "ViewModelFactory", view_model_factory);
    }
};

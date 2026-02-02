#pragma once

#include <data/file_controller.hpp>

class ReadFile
{
    ReadFile(FileController* file_controller) {
        file_controller_ = file_controller;
    };

    void exec(QString file_name) {
        file_controller_->read(file_name);
    };

private:
    FileController* file_controller_;
};

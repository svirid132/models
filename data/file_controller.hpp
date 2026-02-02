#pragma once

#include <QFile>

class FileController {
    using ProgressFn = std::function<void(float progress)>;
    using ErrorFn = std::function<void(QString message)>;
    using FinishFn = std::function<void()>;

public:
    void read(QString fileName, std::function<void(QString)>)
    {
        file.setFileName(fileName);
        file.readAll();
    };

private:
    QFile file;
};

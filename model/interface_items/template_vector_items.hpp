#pragma once

#include <QVariant>

struct ITemplateItems {
    virtual ~ITemplateItems() = default;
    virtual int rowCount() const = 0;
    virtual QVariant data(int row, int role) const = 0;
    virtual bool setData(int row, const QVariant &value, int role) = 0;
    virtual QHash<int, QByteArray> roleNames() const = 0;
};

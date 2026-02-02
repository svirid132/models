#pragma once

#include "interface_items/template_vector_items.hpp"

#include <QAbstractListModel>

class ComposedModel final : public QAbstractListModel {
    Q_OBJECT
public:
    explicit ComposedModel(QObject* parent=nullptr)
        : QAbstractListModel(parent) {}

    int rowCount(const QModelIndex& p) const override
    {
        return template_items_->rowCount();
    }

    QVariant data(const QModelIndex& index, int role) const override
    {
        if (!index.isValid())
        {
            return QVariant();
        }

        int row = index.row();
        return template_items_->data(row, role);
    }

    QHash<int, QByteArray> roleNames() const override
    {
        return template_items_->roleNames();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        if (!index.isValid())
        {
            return false;
        }

        bool ok = template_items_->setData(index.row(), value, role);
        if (ok)
        {
            emit dataChanged(index, index, {role});
        }

        return ok;
    }

    void setTemplateItems(std::unique_ptr<ITemplateItems> template_items)
    {
        beginResetModel();
        template_items_ = std::move(template_items);
        endResetModel();
    }

    // модификаторы изменений
    void beginInsertRows(int first, int last)
    {
        QAbstractListModel::beginInsertRows(QModelIndex(), first, last);
    }

    void endInsertRows()
    {
        QAbstractListModel::endInsertRows();
    }

    void beginRemoveRows(int first, int last)
    {
        QAbstractListModel::beginRemoveRows(QModelIndex(), first, last);
    }

    void endRemoveRows()
    {
        QAbstractListModel::endRemoveRows();
    }

private:
    std::unique_ptr<ITemplateItems> template_items_;
};

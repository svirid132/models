#pragma once

#include <QVariant>

struct ITemplateItems {
    virtual ~ITemplateItems() = default;
    virtual int rowCount() const = 0;
    virtual QVariant data(int row, int role) const = 0;
    virtual bool setData(int row, const QVariant &value, int role) = 0;
    virtual QHash<int, QByteArray> roleNames() const = 0;
};

template<class T>
class TemplateVectorItems final : public ITemplateItems
{
public:
    using DataFn = std::function<QVariant(const T&, int row, int role)>;
    using RolesFn = std::function<QHash<int, QByteArray>()>;
    using SetDataFn = std::function<bool(int, const QVariant&, int)>;

    TemplateVectorItems(QList<T> items = {})
        : items_(std::move(items)) {
    }

    int rowCount() const override
    {
        return items_.size();
    }

    QVariant data(int row, int role) const override
    {
        if (row < 0 || row >= items_.size()) return {};
        return dataFn_ ? dataFn_(items_[row], row, role) : QVariant::fromValue(items_[row]);
    }

    QHash<int, QByteArray> roleNames() const override
    {
        return rolesFn_ ? rolesFn_() : QHash<int, QByteArray>{};
    }

    bool setData(int row, const QVariant &value, int role) override
    {
        return setDataFn_ ? setDataFn_(row, value, role) : true;
    }

    QList<T>& getItems()
    {
        return items_;
    }

    void overrideData(DataFn dataFn)
    {
        dataFn_ = std::move(dataFn);
    }

    void overrideRoleNames(RolesFn rolesFn)
    {
        rolesFn_ = std::move(rolesFn);
    }

    void overrideSetData(SetDataFn setDataFn)
    {
        setDataFn_ = std::move(setDataFn);
    }

private:
    QList<T> items_;
    DataFn dataFn_ = {};
    RolesFn rolesFn_ = {};
    SetDataFn setDataFn_ = {};
};

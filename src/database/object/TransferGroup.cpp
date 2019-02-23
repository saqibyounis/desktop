#include <utility>

//
// Created by veli on 9/25/18.
//

#include "TransferGroup.h"

TransferGroup::TransferGroup(quint32 groupId) : DatabaseObject()
{
    this->groupId = groupId;
}

SqlSelection TransferGroup::getWhere() const
{
    SqlSelection selection;

    selection.setTableName(DbStructure::TABLE_TRANSFERGROUP);
    selection.setWhere(QString("`%1` = ?").arg(DbStructure::FIELD_TRANSFERGROUP_ID));

    selection.whereArgs << QVariant(this->groupId);

    return selection;
}

DbObjectMap TransferGroup::getValues() const
{
    return DbObjectMap{
            {DbStructure::FIELD_TRANSFERGROUP_ID,          QVariant(groupId)},
            {DbStructure::FIELD_TRANSFERGROUP_DATECREATED, QVariant((qlonglong) dateCreated)},
            {DbStructure::FIELD_TRANSFERGROUP_SAVEPATH,    QVariant(savePath)}
    };
}

void TransferGroup::onGeneratingValues(const DbObjectMap &record)
{
    groupId = record.value(DbStructure::FIELD_TRANSFERGROUP_ID).toUInt();
    dateCreated = record.value(DbStructure::FIELD_TRANSFERGROUP_DATECREATED).toLongLong();
    savePath = record.value(DbStructure::FIELD_TRANSFERGROUP_SAVEPATH).toString();
}

TransferAssignee::TransferAssignee(quint32 groupId, const QString &deviceId, const QString &connectionAdapter)
        : DatabaseObject()
{
    this->groupId = groupId;
    this->deviceId = deviceId;
    this->connectionAdapter = connectionAdapter;
}

SqlSelection TransferAssignee::getWhere() const
{
    SqlSelection selection;

    selection.setTableName(DbStructure::TABLE_TRANSFERASSIGNEE);
    selection.setWhere(QString("`%1` = ? AND `%2` = ?")
                               .arg(DbStructure::FIELD_TRANSFERASSIGNEE_DEVICEID)
                               .arg(DbStructure::FIELD_TRANSFERASSIGNEE_GROUPID));

    selection.whereArgs << QVariant(this->deviceId)
                        << QVariant(this->groupId);

    return selection;
}

DbObjectMap TransferAssignee::getValues() const
{
    return DbObjectMap{
            {DbStructure::FIELD_TRANSFERASSIGNEE_DEVICEID,          QVariant(deviceId)},
            {DbStructure::FIELD_TRANSFERASSIGNEE_GROUPID,           QVariant(groupId)},
            {DbStructure::FIELD_TRANSFERASSIGNEE_CONNECTIONADAPTER, QVariant(connectionAdapter)},
            {DbStructure::FIELD_TRANSFERASSIGNEE_ISCLONE,           isClone ? 1 : 0}
    };
}

void TransferAssignee::onGeneratingValues(const DbObjectMap &record)
{
    this->deviceId = record.value(DbStructure::FIELD_TRANSFERASSIGNEE_DEVICEID).toString();
    this->groupId = record.value(DbStructure::FIELD_TRANSFERASSIGNEE_GROUPID).toUInt();
    this->connectionAdapter = record.value(DbStructure::FIELD_TRANSFERASSIGNEE_CONNECTIONADAPTER).toString();
    this->isClone = record.value(DbStructure::FIELD_TRANSFERASSIGNEE_ISCLONE).toInt() == 1;
}

//
// Created by jurek on 26.01.23.
//
#include <QObject>
#include <QTableWidgetItem>

#ifndef SNAKECGP_WIDGETS_MYLISTITEM_H
#define SNAKECGP_WIDGETS_MYLISTITEM_H
class numericalListItem : public QObject, public QTableWidgetItem {
public:
  bool operator<(const QTableWidgetItem &other) const {
    if (this->text().toInt() < other.text().toInt())
      return true;
    else
      return false;
  }
};

#endif // SNAKECGP_WIDGETS_MYLISTITEM_H

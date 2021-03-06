/**
 * @file tools/cathedral/src/MainWindow.h
 * @ingroup cathedral
 *
 * @author COMP Omega <compomega@tutanota.com>
 *
 * @brief Main window definition.
 *
 * Copyright (C) 2012-2020 COMP_hack Team <compomega@tutanota.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TOOLS_CATHEDRAL_SRC_MAINWINDOW_H
#define TOOLS_CATHEDRAL_SRC_MAINWINDOW_H

// Ignore warnings
#include <PushIgnore.h>

// Qt Includes
#include <QMainWindow>

// Stop ignoring warnings
#include <PopIgnore.h>

// libcomp Includes
#include <BinaryDataSet.h>
#include <DataStore.h>
#include <DefinitionManager.h>

namespace objects {

class MiCEventMessageData;
class MiNPCInvisibleData;

}  // namespace objects

namespace Ui {

class MainWindow;

}  // namespace Ui

class DropSetWindow;
class EventWindow;
class ObjectSelectorWindow;
class ZoneWindow;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* pParent = 0);
  ~MainWindow();

  bool Init();

  std::shared_ptr<libcomp::DataStore> GetDatastore() const;
  std::shared_ptr<libhack::DefinitionManager> GetDefinitions() const;

  DropSetWindow* GetDropSets() const;
  EventWindow* GetEvents() const;
  ZoneWindow* GetZones() const;

  std::shared_ptr<objects::MiCEventMessageData> GetEventMessage(
      int32_t msgID) const;

  std::shared_ptr<libhack::BinaryDataSet> GetBinaryDataSet(
      const libcomp::String& objType) const;

  void RegisterBinaryDataSet(
      const libcomp::String& objType,
      const std::shared_ptr<libhack::BinaryDataSet>& dataset,
      bool createSelector = true);

  ObjectSelectorWindow* GetObjectSelector(const libcomp::String& objType) const;

  void UpdateActiveZone(const libcomp::String& path);

  void ResetDropSetCount();
  void ResetEventCount();

  QString GetDialogDirectory();
  void SetDialogDirectory(QString path, bool isFile);

  void CloseSelectors(QWidget* topLevel);

 protected slots:
  void OpenDropSets();
  void OpenEvents();
  void OpenSettings();
  void OpenZone();
  void ViewObjectList();

 protected:
  bool LoadBinaryData(const libcomp::String& binaryFile,
                      const libcomp::String& objName, bool decrypt,
                      bool addSelector = false,
                      bool selectorAllowBlanks = false);

  void CloseAllWindows();

  void closeEvent(QCloseEvent* event) override;

  libcomp::String GetInvisibleDataDescription(
      const std::shared_ptr<objects::MiNPCInvisibleData>& invisibleData);

 private slots:
  void BrowseZone();

 protected:
  DropSetWindow* mDropSetWindow;
  EventWindow* mEventWindow;
  ZoneWindow* mZoneWindow;

 private:
  Ui::MainWindow* ui;

  std::shared_ptr<libcomp::DataStore> mDatastore;
  std::shared_ptr<libhack::DefinitionManager> mDefinitions;

  std::unordered_map<libcomp::String, std::shared_ptr<libhack::BinaryDataSet>>
      mBinaryDataSets;

  std::unordered_map<libcomp::String, ObjectSelectorWindow*> mObjectSelectors;

  libcomp::String mActiveZonePath;
};

static inline QString qs(const libcomp::String& s) {
  return QString::fromUtf8(s.C());
}

static inline libcomp::String cs(const QString& s) {
  return libcomp::String(s.toUtf8().constData());
}

#endif  // TOOLS_CATHEDRAL_SRC_MAINWINDOW_H

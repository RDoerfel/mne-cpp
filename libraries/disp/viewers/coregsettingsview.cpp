//=============================================================================================================
/**
 * @file     coregsettingsview.cpp
 * @author   Ruben Dörfel <doerfelruben@aol.com>
 * @since    0.1.6
 * @date     August, 2020
 *
 * @section  LICENSE
 *
 * Copyright (C) 2020, Ruben Dörfel. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 * the following conditions are met:
 *     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
 *       following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
 *       the following disclaimer in the documentation and/or other materials provided with the distribution.
 *     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
 *       to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @brief    CoregSettingsView class definition.
 *
 */

//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "coregsettingsview.h"
#include "ui_coregsettingsview.h"

#include <fiff/fiff_stream.h>

#include <iostream>
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QSettings>
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>

//=============================================================================================================
// EIGEN INCLUDES
//=============================================================================================================

//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace DISPLIB;

//=============================================================================================================
// DEFINE GLOBAL METHODS
//=============================================================================================================

//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

CoregSettingsView::CoregSettingsView(const QString& sSettingsPath,
                     QWidget *parent,
                     Qt::WindowFlags f)
: AbstractView(parent, f)
, m_pUi(new Ui::CoregSettingsViewWidget)
{
    m_sSettingsPath = sSettingsPath;
    m_pUi->setupUi(this);

    loadSettings();

    // Connect Gui elemnts
    connect(m_pUi->m_qPushButton_BemFileDialog, &QPushButton::released,
            this, &CoregSettingsView::onLoadBemFile);
    connect(m_pUi->m_qPushButton_FidFileDialog, &QPushButton::released,
            this, &CoregSettingsView::onLoadFidFile);
    connect(m_pUi->m_qPushButton_FidStoreFileDialog, &QPushButton::released,
            this, &CoregSettingsView::onStoreFidFile);
    connect(m_pUi->m_qPushButton_DigFileDialog, &QPushButton::released,
            this, &CoregSettingsView::onLoadDigFile);
    connect(m_pUi->m_qPushButton_Omit, &QPushButton::released,
            this, &CoregSettingsView::onDiscardOutliers);



    QPushButton *m_qPushButton_PickLPA;
    QPushButton *m_qPushButton_PickNas;
    QPushButton *m_qPushButton_PickRPA;
    QLabel *m_qLabel_NOmitted;
    QCheckBox *checkBox;
    QWidget *m_qWidget_IcpIterations;
    QSpinBox *spinBox;
    QDoubleSpinBox *m_qDoubleSpinBox_Converge;
    QLineEdit *m_qLineEdit_LpaWeight;
    QLineEdit *m_qLineEdit_NasWeight;
    QLineEdit *m_qLineEdit_RpaWeight;
    QPushButton *m_qPushButton_FitFiducials;
    QPushButton *m_qPushButton_FitICP;
    QSpinBox *m_qSpinBox_X;
    QSpinBox *m_qSpinBox_Y;
    QSpinBox *m_qSpinBox_Z;
    QComboBox *m_qComboBox_ScalingMode;
    QPushButton *m_qPushButton_ApplyScaling;
    QLineEdit *m_qLineEdit_TransX;
    QLineEdit *m_qLineEdit_RotX;
    QLineEdit *m_qLineEdit_TransY;
    QLineEdit *m_qLineEdit_RotY;
    QLineEdit *m_qLineEdit_TransZ;
    QLineEdit *m_qLineEdit_RotZ;
    QLineEdit *m_qLineEdit_TransFileStore;
    QPushButton *m_qPushButton_TransFileStoreDialaog;
}

//=============================================================================================================

CoregSettingsView::~CoregSettingsView()
{
    saveSettings();
    delete m_pUi;
}

//=============================================================================================================

void CoregSettingsView::saveSettings()
{
    if(m_sSettingsPath.isEmpty()) {
        return;
    }

    // Save Settings
    QSettings settings("MNECPP");

}

//=============================================================================================================

void CoregSettingsView::loadSettings()
{
    if(m_sSettingsPath.isEmpty()) {
        return;
    }

    // Load Settings
    QSettings settings("MNECPP");

}

//=============================================================================================================

void CoregSettingsView::updateGuiMode(GuiMode mode)
{
    switch(mode) {
    case GuiMode::Clinical:
        break;
    default: // default is research mode
        break;
    }
}

//=============================================================================================================

void CoregSettingsView::updateProcessingMode(ProcessingMode mode)
{
    switch(mode) {
    case ProcessingMode::Offline:
        break;
    default: // default is realtime mode
        break;
    }
}

//=============================================================================================================

void CoregSettingsView::onLoadBemFile()
{
    QString t_sFileName = QFileDialog::getOpenFileName(this,
                                                       tr("Select Bem Model"),
                                                       QString(),
                                                       tr("Fif Files (*.fif)"));

    QFile t_fBem(t_sFileName);
    if(t_fBem.open(QIODevice::ReadOnly)) {
        m_pUi->m_qLineEdit_BemFileName->setText(t_sFileName);
    } else {
        qWarning() << "[disp::CoregSettingsView] Bem file cannot be opened";
    }
    t_fBem.close();

    emit bemFileChanged(t_sFileName);
}

//=============================================================================================================

void CoregSettingsView::onLoadFidFile()
{
    QString t_sFileName = QFileDialog::getOpenFileName(this,
                                                       tr("Select fiducials"),
                                                       QString(),
                                                       tr("Fif Files (*.fif)"));

    QFile t_fFid(t_sFileName);
    if(t_fFid.open(QIODevice::ReadOnly)) {
        m_pUi->m_qLineEdit_FidFileName->setText(t_sFileName);
    } else {
        qWarning() << "[disp::CoregSettingsView] Fiducial file cannot be opened";
    }
    t_fFid.close();

    emit fidFileChanged(t_sFileName);
}

//=============================================================================================================

void CoregSettingsView::onStoreFidFile()
{
    QString t_sDirName = QFileDialog::getExistingDirectory(this,
                                                           tr("Open directory to store fiducials"),
                                                           QString(),
                                                           QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);

    QString t_sFileName = m_pUi->m_qLineEdit_FidStoreFileName->text();
    QString t_sFilePath(t_sDirName + '/' + t_sFileName);
    m_pUi->m_qLineEdit_FidStoreFileName->setText(t_sFilePath);

    emit fidStoreFileChanged(t_sFilePath);
}

//=============================================================================================================

void CoregSettingsView::onLoadDigFile()
{
    QString t_sFileName = QFileDialog::getOpenFileName(this,
                                                       tr("Select digitizer file"),
                                                       QString(),
                                                       tr("Fif Files (*.fif)"));

    QFile t_fDigid(t_sFileName);
    if(t_fDigid.open(QIODevice::ReadOnly)) {
        m_pUi->m_qLineEdit_DigFileName->setText(t_sFileName);
    } else {
        qWarning() << "[disp::CoregSettingsView] Digitizer file cannot be opened";
    }
    t_fDigid.close();

    emit digFileChanged(t_sFileName);
}

//=============================================================================================================

void CoregSettingsView::onDiscardOutliers()
{
    float fMaxDist = m_pUi->m_qSpinBox_Discard->value()/1000;
    emit omitDgitizer(fMaxDist);
}

//=============================================================================================================
/**
 * @file     view3d.cpp
 * @author   Lorenz Esch <lesch@mgh.harvard.edu>
 * @since    0.1.6
 * @date     August, 2020
 *
 * @section  LICENSE
 *
 * Copyright (C) 2020, Lorenz Esch. All rights reserved.
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
 * @brief    View3D class defintion.
 *
 */

//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "view3d.h"

#include <anShared/Management/communicator.h>
#include <anShared/Management/analyzedata.h>
#include <anShared/Model/bemdatamodel.h>
#include <disp3D/viewers/sourceestimateview.h>
#include <disp3D/engine/view/view3D.h>
#include <disp3D/engine/model/data3Dtreemodel.h>
#include <disp3D/engine/delegate/data3Dtreedelegate.h>

#include <disp/viewers/control3dview.h>

//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QDebug>

//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace VIEW3DPLUGIN;
using namespace ANSHAREDLIB;
using namespace DISPLIB;

//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

View3D::View3D()
: m_pCommu(Q_NULLPTR)
{
}

//=============================================================================================================

View3D::~View3D()
{
}

//=============================================================================================================

QSharedPointer<IPlugin> View3D::clone() const
{
    QSharedPointer<View3D> pView3DClone(new View3D);
    return pView3DClone;
}

//=============================================================================================================

void View3D::init()
{
    m_pCommu = new Communicator(this);
    m_p3DModel = QSharedPointer<DISP3DLIB::Data3DTreeModel>::create();
}

//=============================================================================================================

void View3D::unload()
{

}

//=============================================================================================================

QString View3D::getName() const
{
    return "3D View";
}

//=============================================================================================================

QMenu *View3D::getMenu()
{
    return Q_NULLPTR;
}

//=============================================================================================================

QWidget *View3D::getView()
{
    m_pView3D = new DISP3DLIB::View3D();
    m_pView3D->setModel(m_p3DModel);
    QWidget *pWidgetContainer = QWidget::createWindowContainer(m_pView3D, Q_NULLPTR, Qt::Widget);

    return pWidgetContainer;
}

//=============================================================================================================

QDockWidget* View3D::getControl()
{
    // Coregistration Settings
    DISP3DLIB::Data3DTreeDelegate* pData3DTreeDelegate = new DISP3DLIB::Data3DTreeDelegate(this);

    m_pControl3DView = new DISPLIB::Control3DView(QString("MNEANALYZE/%1").arg(this->getName()));
    m_pControl3DView->setDelegate(pData3DTreeDelegate);
    m_pControl3DView->setModel(m_p3DModel.data());

    QDockWidget* pControlDock = new QDockWidget(getName());
    pControlDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    pControlDock->setWidget(m_pControl3DView);
    pControlDock->setObjectName(getName());

    return pControlDock;
}

//=============================================================================================================

void View3D::handleEvent(QSharedPointer<Event> e)
{
    switch (e->getType()) {
    case SELECTED_MODEL_CHANGED:
        updateBemList(e->getData().value<QSharedPointer<ANSHAREDLIB::AbstractModel>>());
        break;
        default:
            qWarning() << "[View3D::handleEvent] Received an Event that is not handled by switch cases.";
    }
}

//=============================================================================================================

QVector<EVENT_TYPE> View3D::getEventSubscriptions(void) const
{
    QVector<EVENT_TYPE> temp;
    temp.push_back(SELECTED_MODEL_CHANGED);

    return temp;
}

//=============================================================================================================

void View3D::updateBemList(ANSHAREDLIB::AbstractModel::SPtr pNewModel)
{
    if(pNewModel->getType() == ANSHAREDLIB_BEMDATA_MODEL) {
        QSharedPointer<ANSHAREDLIB::BemDataModel> pBemDataModel = qSharedPointerCast<BemDataModel>(pNewModel);
        m_pBemTreeCoreg = m_p3DModel->addBemData("Subject", "Average head", *pBemDataModel->getBem().data());
    }
}

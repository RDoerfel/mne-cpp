//=============================================================================================================
/**
* @file     edf_info.h
* @author   Simon Heinke <simon.heinke@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     April, 2019
*
* @section  LICENSE
*
* Copyright (C) 2019, Simon Heinke and Matti Hamalainen. All rights reserved.
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
* @brief    Contains the declaration of the EDFInfo class.
*
*/

#ifndef EDF_INFO_H
#define EDF_INFO_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "edf_signal_info.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QDateTime>
#include <QVector>


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

class QIODevice;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE EDFINFOEXAMPLE
//=============================================================================================================

namespace EDFINFOEXAMPLE
{


//=============================================================================================================
/**
* DECLARE CLASS EDFInfo
*
* @brief The EDFInfo holds all relevant information for EDF files.
*/
class EDFInfo
{

public:
    //=========================================================================================================
    /**
    * Constructs an EDFInfo by parsing the header of the passed edf file pDev.
    */
    EDFInfo();

    //=========================================================================================================
    /**
    * Constructs an EDFInfo by parsing the passed IO device.
    */
    EDFInfo(QIODevice* pDev);

    //=========================================================================================================
    /**
    * Obtain textual representation of signal.
    *
    * @return Textual representation of signal.
    */
    QString getAsString() const;

    inline QVector<EDFSignalInfo> getMeasurementSignalInfos() const;

    inline int getNumberOfDataRecords() const;

    inline int getNumberOfSignals() const;

private:
    // data fields for EDF header. The member order does not correlate with the position in the header.
    QString     m_sEDFVersionNo;
    QString     m_sLocalPatientIdentification;
    QString     m_sLocalRecordingIdentification;
    QDateTime   m_startDateTime;
    int         m_iNumBytesInHeader;
    int         m_iNumDataRecords;
    float       m_fDataRecordsDuration;
    int         m_iNumSignals;

    // vector of all signals that (probably) contain continuous measurement data
    QVector<EDFSignalInfo>  m_vMeasurementSignals;
    // vector for all other signals, e.g. stimuli etc.
    QVector<EDFSignalInfo>  m_vExtraSignals;
};

//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================


inline QVector<EDFSignalInfo> EDFInfo::getMeasurementSignalInfos() const {
    return m_vMeasurementSignals;
}


//*************************************************************************************************************

inline int EDFInfo::getNumberOfDataRecords() const {
    return m_iNumDataRecords;
}


//*************************************************************************************************************

inline int EDFInfo::getNumberOfSignals() const {
    return m_iNumSignals;
}

} // NAMESPACE

#endif // EDF_INFO_H

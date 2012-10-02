//=============================================================================================================
/**
* @file     fiff_id.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hämäläinen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     July, 2012
*
* @section  LICENSE
*
* Copyright (C) 2012, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Contains the FiffId class declaration.
*
*/

#ifndef FIFF_ID_H
#define FIFF_ID_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "../fiff_global.h"
#include "fiff_types.h"


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE FIFFLIB
//=============================================================================================================

namespace FIFFLIB
{

//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================


//=============================================================================================================
/**
* DECLARE CLASS FiffId, replaces fiffIdRec which had a size of 5*4 = 20
*
* A file ID.
*
* These universially unique identifiers are also
* used to identify blocks within the files.
*
* typedef struct _fiffIdRec {
*  fiff_int_t version;     /**< File version *
*  fiff_int_t machid[2];   /**< Unique machine ID *
*  fiffTimeRec time;       /**< Time of the ID creation *
*} fiffIdRec,*fiffId;     /**< This is the file identifier *
*
* typedef fiffIdRec fiff_id_t;
*
* @brief The FiffId class provides the fiff file id description
**/

class FIFFSHARED_EXPORT FiffId {

public:
    //=========================================================================================================
    /**
    * ctor
    */
    FiffId();

    //=========================================================================================================
    /**
    * Destroys the FiffInfo.
    */
    ~FiffId();

    //=========================================================================================================
    /**
    * Size of the old struct (fiffIdRec) 5*int = 5*4 = 20
    *
    * @return the size of the old struct fiffIdRec.
    */
    inline static qint32 size();

public:
    fiff_int_t version;     /**< File version */
    fiff_int_t machid[2];   /**< Unique machine ID */
    fiffTimeRec time;       /**< Time of the ID creation */
};


//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================

inline qint32 FiffId::size()
{
    return 20;
}

} // NAMESPACE

#endif // FIFF_ID_H

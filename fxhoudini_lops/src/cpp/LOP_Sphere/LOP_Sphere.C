/*
 * Copyright (c) 2009
 *    Side Effects Software Inc.  All rights reserved.
 *
 * Redistribution and use of Houdini Development Kit samples in source and
 * binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. The name of Side Effects Software may not be used to endorse or
 *    promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY SIDE EFFECTS SOFTWARE `AS IS' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO EVENT SHALL SIDE EFFECTS SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *----------------------------------------------------------------------------
 * The Surface SOP.  This SOP Surfaces the volume into polygons.
 */

#include "LOP_Sphere.h"

// This is an automatically generated header file based on theDsFile, below,
// to provide SOP_StarParms, an easy way to access parameter values from
// SOP_StarVerb::cook with the correct type.
// #include "LOP_Sphere.proto.h"

#include <iostream>
#include <LOP/LOP_PRMShared.h>
#include <LOP/LOP_Error.h>
#include <HUSD/HUSD_CreatePrims.h>
#include <HUSD/HUSD_Constants.h>
#include <HUSD/HUSD_Utils.h>
#include <HUSD/HUSD_SetAttributes.h>
#include <HUSD/HUSD_DataHandle.h>
#include <HUSD/XUSD_Data.h>
#include <HUSD/XUSD_Utils.h>
#include <gusd/USD_VisCache.h>
#include <OP/OP_OperatorTable.h>
#include <OP/OP_Operator.h>
#include <PRM/PRM_Include.h>
#include <UT/UT_DSOVersion.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usdGeom/tokens.h>

using namespace HDK_Sample;
PXR_NAMESPACE_USING_DIRECTIVE

// const UT_StringHolder LOP_Sphere::theLOPTypeName("hdk_sphere"_sh);

void
newLopOperator(OP_OperatorTable *table)
{
    table->addOperator(new OP_Operator(
        // LOP_LOP_Sphere::theLOPTypeName,
        "hdk_sphere",
        "Sphere",
        LOP_Sphere::myConstructor,
        LOP_Sphere::myTemplateList,
        (unsigned)0,
        (unsigned)1));
}

static PRM_Name		 theRadiusName("radius", "Radius");
static PRM_Name		 theTestName("testradius", "TestRadius");
static PRM_Name		 visibilityName("visibility", "Visibility");

PRM_Template
LOP_Sphere::myTemplateList[] = {
    PRM_Template(PRM_STRING, 1, &lopPrimPathName,
		 &lopAddPrimPathDefault, &lopPrimPathMenu,
		 0, 0, &lopPrimPathSpareData),
    PRM_Template(PRM_FLT,    1, &theRadiusName, PRMoneDefaults),
    PRM_Template(PRM_TOGGLE_E,    1, &visibilityName, PRMoneDefaults),
    PRM_Template(PRM_FLT,    1, &theTestName, PRMoneDefaults),
    PRM_Template(),
};

OP_Node *
LOP_Sphere::myConstructor(OP_Network *net, const char *name, 
OP_Operator *op)
{
    return new LOP_Sphere(net, name, op);
}

LOP_Sphere::LOP_Sphere(OP_Network *net, const char *name, OP_Operator *op)
    : LOP_Node(net, name, op)
{
}

LOP_Sphere::~LOP_Sphere()
{
}

void
LOP_Sphere::PRIMPATH(UT_String &str, fpreal t)
{
    evalString(str, lopPrimPathName.getToken(), 0, t);
    HUSDmakeValidUsdPath(str);
}

fpreal
LOP_Sphere::RADIUS(fpreal t)
{
    return evalFloat(theRadiusName.getToken(), 0, t);
}

fpreal
LOP_Sphere::VISIBILITY(fpreal t)
{
    return evalFloat(visibilityName.getToken(), 0, t);


}

OP_ERROR
LOP_Sphere::cookMyLop(OP_Context &context)
{
    // Cook the node connected to our input, and make a "soft copy" of the
    // result into our own HUSD_DataHandle.
    if (cookModifyInput(context) >= UT_ERROR_FATAL)
	return error();

    UT_String		     primpath;
    fpreal		     radius;
    fpreal           vis;

    PRIMPATH(primpath, context.getTime());
    radius = RADIUS(context.getTime());
    vis = VISIBILITY(context.getTime());
    TfToken vis_string = (int(vis) == 1) ? UsdGeomTokens->inherited :  UsdGeomTokens->invisible;
    const TfToken primvarsDisplayOpacity;

    // Use editableDataHandle to get non-const access to our data handle, and
    // the lock it for writing. This makes sure that the USD stage is set up
    // to match the configuration defined in our data handle. Any edits made
    // to the stage at this point will be preserved in our data handle when
    // we unlock it.
    HUSD_AutoWriteLock	     writelock(editableDataHandle());

    // Create a helper class for creating USD primitives on the stage.
    HUSD_CreatePrims	     creator(writelock);

    // Use the helper class to create a new "Sphere" primitive, with a
    // specifier type of "def" to define this primitive even if it doesn't
    // exist on the stage yet.
    //
    // The "empty string" parameter to createPrim tells it to not author HUSD_CreatePrimsa
    // "kind" setting for this primiitve.
    if (!creator.createPrim(primpath, "UsdGeomSphere",
	    UT_StringHolder::theEmptyString,
	    HUSD_Constants::getPrimSpecifierDefine(),
	    HUSD_Constants::getXformPrimType()))
	addError(LOP_PRIM_NOT_CREATED, primpath);

    // Use direct editing of the USD stage to modify the radius attribute
    // of the new sphere primitive. We could use the HUSD_SetAttributes
    // helper class here, but this demonstrates that we are allowed to
    // access the stage directly. The edit target will already be set to
    // the "active layer", and as long as we leave it there, any changes
    // we make will be preserved by our data handle.
    UsdStageRefPtr	     stage = writelock.data()->stage();
    SdfPath		     sdfpath(HUSDgetSdfPath(primpath));
    UsdPrim		     prim = stage->GetPrimAtPath(sdfpath);

    if (prim)
	prim.GetAttribute(UsdGeomTokens->radius).Set(radius);
	prim.GetAttribute(UsdGeomTokens->visibility).Set(vis_string);
    // bool test = GusdUSD_VisCache::GetInstance().GetVisibility(prim, context.getTime());
    // std::cout << UsdGeomTokens->visibility << std::endl;

    setLastModifiedPrims(primpath);

    return error();
}


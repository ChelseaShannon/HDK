#include "SOP_myAsset.h"


#include <GU/GU_Detail.h>
#include <OP/OP_AutoLockInputs.h>
#include <GEO/GEO_PrimPoly.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <PRM/PRM_TemplateBuilder.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <UT/UT_StringHolder.h>
#include <SYS/SYS_Math.h>
#include <limits.h>

using namespace HDK_Sample;


// Provide entry point for installing this SOP.
void
newSopOperator(OP_OperatorTable *table)
{
    OP_Operator *op = new OP_Operator(
        "uv_texturebake",
        "TextureBakeExport",
        SOP_myAsset::myConstructor,
        SOP_myAsset::myTemplateList,
        1,      // min inputs
        1       // max inputs
        );
    table->addOperator(op);
}


OP_Node *
SOP_myAsset::myConstructor(
        OP_Network *net, const char *name, OP_Operator *op)
{
    return new SOP_myAsset(net, name, op);
}


// SOP Parameters.
static PRM_Name names[] =
{
    PRM_Name("display",        "Display"),
    PRM_Name("input",          "Input"),
    PRM_Name("type",           "Type"),
    PRM_Name("attribute",      "Attribute"),
    PRM_Name("asset_name",     "Asset Name"),
};

static PRM_Name display_Choices[] =
	{
		PRM_Name("uvpace", "Uvs"),
		PRM_Name("3d", "3d view"),
        PRM_Name(0)
	};



static PRM_Name input_Choices[] =
	{
		PRM_Name("attribute", "Attribute"),
		PRM_Name("group", "Group"),
        PRM_Name(0)
	};


static PRM_Name type_Choices[] =
	{
		PRM_Name("point", "Point"),
		PRM_Name("prim", "Prim"),
        PRM_Name(0)
	};

static PRM_ChoiceList   displayMenu(PRM_CHOICELIST_SINGLE, display_Choices);
static PRM_ChoiceList   inputMenu(PRM_CHOICELIST_SINGLE, input_Choices);
static PRM_ChoiceList   typeMenu(PRM_CHOICELIST_SINGLE, type_Choices);



static PRM_Default  sopThresholdDefault(1e-03f);
PRM_Template SOP_myAsset::myTemplateList[] =
{
    PRM_Template(PRM_STRING, 1, &names[0], 0, &displayMenu),  // Ordered string simple menu
    PRM_Template(PRM_ORD,    1, &names[1], 0, &inputMenu),    // Ordered ordered simple menu
    PRM_Template(PRM_ORD,    1, &names[2], 0, &typeMenu),
    PRM_Template(PRM_STRING, 1, &names[3], 0, &SOP_Node::allGroupMenu),
    PRM_Template() // sentinel
};


// Constructor
SOP_myAsset::SOP_myAsset(OP_Network *net, const char *name, OP_Operator *op)
    : SOP_Node(net, name, op)
{
    mySopFlags.setManagesDataIDs(true);
}


// Destructor
SOP_myAsset::~SOP_myAsset(){}






// void
// SOP_myAsset::populateAttributMenu()
// {
//     // SEARCH: get whether we want to export an attribute or group
    
    


//     // TYPE: get whether it is a prim or point group/attribute - TODO handle all attribute types


//     // If group:
//     // Get group based on type.
//         ////SOP_Node::primGroupMenu
//         ////SOP_Node::pointGroupMenu

//     //If attribute
//     //Get attributes based on type


//     // Return as menu
// }

OP_ERROR
SOP_myAsset::cookMySop(OP_Context &context)
{
    // We must lock our inputs before we try to access their geometry.
    // OP_AutoLockInputs will automatically unlock our inputs when we return.
    // NOTE: Don't call unlockInputs yourself when using this!
    OP_AutoLockInputs inputs(this);
    if (inputs.lock(context) >= UT_ERROR_ABORT)
        return error();

    // NOTE: No data IDs need to be bumped when just renaming an attribute,
    //       because the data is considered to exclude the name.
    return error();
}

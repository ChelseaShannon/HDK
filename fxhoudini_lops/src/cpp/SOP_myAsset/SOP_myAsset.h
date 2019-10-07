#ifndef __SOP_myAsset_h__
#define __SOP_myAsset_h__

#include <SOP/SOP_Node.h>
#include <UT/UT_StringHolder.h>

namespace HDK_Sample {
    
/// This is the SOP class definition.  It doesn't need to be in a separate
/// file like this.  This is just an example of a header file, in case
/// another file needs to reference something in here.
/// You shouldn't have to change anything in here except the name of the class.
class SOP_myAsset : public SOP_Node
{
public:
    SOP_myAsset(OP_Network *net, const char *, OP_Operator *entry);
    virtual ~SOP_myAsset();
    
    static PRM_Template          myTemplateList[];
    static OP_Node              *myConstructor(OP_Network  *net, const char *name, OP_Operator *entry);


    virtual OP_ERROR             cookInputGroups(OP_Context &context, 
                                                int alone = 0);

   //static void populateAttributMenu()

protected:
    virtual OP_ERROR             cookMySop(OP_Context &context);

private:
    void        getGroups(UT_String &str){ evalString(str, "group", 0, 0); }
    fpreal      AMP(fpreal t)           { return evalFloat("amp", 0, t); }

    /// This is the group of geometry to be manipulated by this SOP and cooked
    /// by the method "cookInputGroups".
    const GA_PointGroup *myGroup;

};

} // End HDK_Sample namespace
#endif

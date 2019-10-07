/*
 * Copyright (c) 2009
 *    Side Effects Software Inc.  All rights reserved.
 *
 * Redistribution and use of Houdini Development Kit samples in source and
 * binary forms, with or without modification, are permitted provided 
that the
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
 * Surface SOP
 */


#ifndef __LOP_Sphere_h__
#define __LOP_Sphere_h__

#include <LOP/LOP_Node.h>

namespace HDK_Sample {

class LOP_Sphere : public LOP_Node
{
public:
			 LOP_Sphere(OP_Network *net, const char *name,
				 OP_Operator *op);
    virtual		~LOP_Sphere();

    static PRM_Template	 myTemplateList[];
    static OP_Node	*myConstructor(OP_Network *net, const char *name,
                                OP_Operator *op);
protected:
    /// Method to cook USD data for the LOP
    virtual OP_ERROR     cookMyLop(OP_Context &context);

private:
    void		 PRIMPATH(UT_String&str, fpreal t);
    fpreal		 RADIUS(fpreal t);
    fpreal       VISIBILITY(fpreal t);
};

} // End HDK_Sample namespace

#endif

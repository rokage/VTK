/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkImplicitFunction.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkImplicitFunction - abstract interface for implicit functions
// .SECTION Description
// vtkImplicitFunction specifies an abstract interface for implicit 
// functions. Implicit functions are real valued functions defined in 3D 
// space, w = F(x,y,z). Two primitive 
// operations are required: the ability to evaluate the function, and the 
// function gradient at a given point.
//
// Implicit functions are very powerful. It is possible to represent almost
// any type of geometry with the level sets w = const, especially if you use 
// boolean combinations of implicit functions (see vtkImplicitBoolean).
//
// vtkImplicitFunction provides a mechanism to transform the implicit
// function(s) via a vtkAbstractTransform.  This capability can be used to 
// translate, orient, scale, or warp implicit functions.  For example, 
// a sphere implicit function can be transformed into an oriented ellipse. 

// .SECTION Caveats
// The transformation transforms a point into the space of the implicit
// function (i.e., the model space). Typically we want to transform the 
// implicit model into world coordinates. In this case the inverse of the 
// transformation is required.

// .SECTION See Also
// vtkAbstractTransform vtkSphere vtkCylinder vtkImplicitBoolean vtkPlane 
// vtkPlanes vtkQuadric vtkImplicitVolume vtkSampleFunction vtkCutter
// vtkClipPolyData

#ifndef __vtkImplicitFunction_h
#define __vtkImplicitFunction_h

#include "vtkObject.h"
#include "vtkAbstractTransform.h"

class VTK_COMMON_EXPORT vtkImplicitFunction : public vtkObject
{
public:
  vtkTypeRevisionMacro(vtkImplicitFunction,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Overload standard modified time function. If Transform is modified,
  // then this object is modified as well.
  unsigned long GetMTime();

  // Description:
  // Evaluate function at position x-y-z and return value. Point x[3] is
  // transformed through transform (if provided).
  float FunctionValue(const float x[3]);
  float FunctionValue(float x, float y, float z) {
    float xyz[3] = {x, y, z}; return this->FunctionValue(xyz); };

  // Description:
  // Evaluate function gradient at position x-y-z and pass back vector. Point
  // x[3] is transformed through transform (if provided).
  void FunctionGradient(const float x[3], float g[3]);
  float *FunctionGradient(const float x[3]) {
    this->FunctionGradient(x,this->ReturnValue);
    return this->ReturnValue; };
  float *FunctionGradient(float x, float y, float z) {
    float xyz[3] = {x, y, z}; return this->FunctionGradient(xyz); };

  // Description:
  // Set/Get a transformation to apply to input points before
  // executing the implicit function.
  vtkSetObjectMacro(Transform,vtkAbstractTransform);
  vtkGetObjectMacro(Transform,vtkAbstractTransform);

  // Description:
  // Evaluate function at position x-y-z and return value.  You should
  // generally not call this method directly, you should use 
  // FunctionValue() instead.  This method must be implemented by 
  // any derived class. 
  virtual float EvaluateFunction(float x[3]) = 0;
  float EvaluateFunction(float x, float y, float z) {
    float xyz[3] = {x, y, z}; return this->EvaluateFunction(xyz); };

  // Description:
  // Evaluate function gradient at position x-y-z and pass back vector. 
  // You should generally not call this method directly, you should use 
  // FunctionGradient() instead.  This method must be implemented by 
  // any derived class. 
  virtual void EvaluateGradient(float x[3], float g[3]) = 0;

protected:
  vtkImplicitFunction();
  ~vtkImplicitFunction();

  vtkAbstractTransform *Transform;
  float ReturnValue[3];
private:
  vtkImplicitFunction(const vtkImplicitFunction&);  // Not implemented.
  void operator=(const vtkImplicitFunction&);  // Not implemented.
};

#endif

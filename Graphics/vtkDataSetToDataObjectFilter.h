/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkDataSetToDataObjectFilter.h
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
// .NAME vtkDataSetToDataObjectFilter - map dataset into data object (i.e., a field)
// .SECTION Description
// vtkDataSetToDataObjectFilter is an class that transforms a dataset into
// data object (i.e., a field). The field will have labeled data arrays
// corresponding to the topology, geometry, field data, and point and cell
// attribute data.
//
// You can control what portions of the dataset are converted into the
// output data object's field data. The instance variables Geometry,
// Topology, FieldData, PointData, and CellData are flags that control
// whether the dataset's geometry (e.g., points, spacing, origin);
// topology (e.g., cell connectivity, dimensions); the field data
// associated with the dataset's superclass data object; the dataset's
// point data attributes; and the dataset's cell data attributes. (Note:
// the data attributes include scalars, vectors, tensors, normals, texture
// coordinates, and field data.)
//
// The names used to create the field data are as follows. For vtkPolyData, 
// "Points", "Verts", "Lines", "Polys", and "Strips". For vtkUnstructuredGrid,
// "Cells" and "CellTypes". For vtkStructuredPoints, "Dimensions", "Spacing", 
// and "Origin". For vtkStructuredGrid, "Points" and "Dimensions". For
// vtkRectilinearGrid, "XCoordinates", "YCoordinates", and "ZCoordinates".
// for point attribute data, "PointScalars", "PointVectors", etc. For cell
// attribute data, "CellScalars", "CellVectors", etc. Field data arrays retain
// their original name.

// .SECTION See Also
// vtkDataObject vtkFieldData vtkDataObjectToDataSetFilter

#ifndef __vtkDataSetToDataObjectFilter_h
#define __vtkDataSetToDataObjectFilter_h

#include "vtkDataObjectSource.h"
#include "vtkDataSet.h"
#include "vtkCollection.h"

class VTK_GRAPHICS_EXPORT vtkDataSetToDataObjectFilter : public vtkDataObjectSource
{
public:
  vtkTypeRevisionMacro(vtkDataSetToDataObjectFilter,vtkDataObjectSource);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Instantiate the object to transform all data into a data object.
  static vtkDataSetToDataObjectFilter *New();

  // Description:
  // Turn on/off the conversion of dataset geometry to a data object.
  vtkSetMacro(Geometry,int);
  vtkGetMacro(Geometry,int);
  vtkBooleanMacro(Geometry,int);

  // Description:
  // Turn on/off the conversion of dataset topology to a data object.
  vtkSetMacro(Topology,int);
  vtkGetMacro(Topology,int);
  vtkBooleanMacro(Topology,int);

  // Description:
  // Turn on/off the conversion of dataset field data to a data object.
  vtkSetMacro(FieldData,int);
  vtkGetMacro(FieldData,int);
  vtkBooleanMacro(FieldData,int);

  // Description:
  // Turn on/off the conversion of dataset point data to a data object.
  vtkSetMacro(PointData,int);
  vtkGetMacro(PointData,int);
  vtkBooleanMacro(PointData,int);

  // Description:
  // Turn on/off the conversion of dataset cell data to a data object.
  vtkSetMacro(CellData,int);
  vtkGetMacro(CellData,int);
  vtkBooleanMacro(CellData,int);

  // Description:
  // Cast input to DataSet.
  virtual void SetInput(vtkDataSet *input);
  vtkDataSet *GetInput();

protected:
  vtkDataSetToDataObjectFilter();
  ~vtkDataSetToDataObjectFilter();

  void Execute(); //generate output data
  void ComputeInputUpdateExtents(vtkDataObject *output);
  
  int Geometry;
  int Topology;
  int PointData;
  int CellData;
  int FieldData;

private:
  vtkDataSetToDataObjectFilter(const vtkDataSetToDataObjectFilter&);  // Not implemented.
  void operator=(const vtkDataSetToDataObjectFilter&);  // Not implemented.
};

#endif



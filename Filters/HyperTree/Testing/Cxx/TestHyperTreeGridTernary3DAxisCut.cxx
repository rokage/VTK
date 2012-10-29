/*=========================================================================

  Copyright (c) Kitware Inc.
  All rights reserved.

=========================================================================*/
// .SECTION Thanks
// This test was written by Philippe Pebay and Charles Law, Kitware 2012
// This work was supported in part by Commissariat a l'Energie Atomique (CEA/DIF)

#include "vtkHyperTreeGrid.h"
#include "vtkHyperTreeGridAxisCut.h"
#include "vtkHyperTreeGridSource.h"

#include "vtkCamera.h"
#include "vtkCellData.h"
#include "vtkNew.h"
#include "vtkOutlineFilter.h"
#include "vtkProperty.h"
#include "vtkPolyDataMapper.h"
#include "vtkRegressionTestImage.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

int TestHyperTreeGridTernary3DAxisCut( int argc, char* argv[] )
{
  // Hyper tree grid
  vtkNew<vtkHyperTreeGridSource> htGrid;
  int maxLevel = 5;
  htGrid->SetMaximumLevel( maxLevel );
  htGrid->SetGridSize( 3, 3, 2 );
  htGrid->SetGridScale( 1.5, 1., .7 );
  htGrid->SetDimension( 3 );
  htGrid->SetAxisBranchFactor( 3 );
  htGrid->DualOn();
  htGrid->SetDescriptor( "RRR .R. .RR ..R ..R .R.|R.......................... ........................... ........................... .............R............. ....RR.RR........R......... .....RRRR.....R.RR......... ........................... ........................... ...........................|........................... ........................... ........................... ...RR.RR.......RR.......... ........................... RR......................... ........................... ........................... ........................... ........................... ........................... ........................... ........................... ............RRR............|........................... ........................... .......RR.................. ........................... ........................... ........................... ........................... ........................... ........................... ........................... ...........................|........................... ..........................." );

  // Outline
  vtkNew<vtkOutlineFilter> outline;
  outline->SetInputConnection( htGrid->GetOutputPort() );

  // Axis cuts
  vtkNew<vtkHyperTreeGridAxisCut> axisCut1;
  axisCut1->SetInputConnection( htGrid->GetOutputPort() );
  axisCut1->SetPlaneNormalAxis( 0 );
  axisCut1->SetPlanePosition( 2. );
  axisCut1->Update();
  vtkNew<vtkHyperTreeGridAxisCut> axisCut2;
  axisCut2->SetInputConnection( htGrid->GetOutputPort() );
  axisCut2->SetPlaneNormalAxis( 2 );
  axisCut2->SetPlanePosition( .35 );
  axisCut2->Update();
  vtkPolyData* pd = axisCut2->GetOutput();

  // Mappers
  vtkNew<vtkPolyDataMapper> mapper1;
  mapper1->SetInputConnection( axisCut1->GetOutputPort() );
  mapper1->SetScalarRange( pd->GetCellData()->GetScalars()->GetRange() );
  mapper1->SetResolveCoincidentTopologyToPolygonOffset();
  mapper1->SetResolveCoincidentTopologyPolygonOffsetParameters( 0, 1 );
  vtkNew<vtkPolyDataMapper> mapper2;
  mapper2->SetInputConnection( axisCut1->GetOutputPort() );
  mapper2->ScalarVisibilityOff();
  mapper2->SetResolveCoincidentTopologyToPolygonOffset();
  mapper2->SetResolveCoincidentTopologyPolygonOffsetParameters( 1, 1 );
  vtkNew<vtkPolyDataMapper> mapper3;
  mapper3->SetInputConnection( outline->GetOutputPort() );
  mapper3->ScalarVisibilityOff();
  vtkNew<vtkPolyDataMapper> mapper4;
  mapper4->SetInputConnection( axisCut2->GetOutputPort() );
  mapper4->SetScalarRange( pd->GetCellData()->GetScalars()->GetRange() );
  mapper4->SetResolveCoincidentTopologyToPolygonOffset();
  mapper4->SetResolveCoincidentTopologyPolygonOffsetParameters( 0, 1 );
  vtkNew<vtkPolyDataMapper> mapper5;
  mapper5->SetInputConnection( axisCut2->GetOutputPort() );
  mapper5->ScalarVisibilityOff();
  mapper5->SetResolveCoincidentTopologyToPolygonOffset();
  mapper5->SetResolveCoincidentTopologyPolygonOffsetParameters( 1, 1 );
 
  // Actors
  vtkNew<vtkActor> actor1;
  actor1->SetMapper( mapper1.GetPointer() );
  vtkNew<vtkActor> actor2;
  actor2->SetMapper( mapper2.GetPointer() );
  actor2->GetProperty()->SetRepresentationToWireframe();
  actor2->GetProperty()->SetColor( .7, .7, .7 );
  vtkNew<vtkActor> actor3;
  actor3->SetMapper( mapper3.GetPointer() );
  actor3->GetProperty()->SetColor( .1, .1, .1 );
  actor3->GetProperty()->SetLineWidth( 1 );
  vtkNew<vtkActor> actor4;
  actor4->SetMapper( mapper4.GetPointer() );
  vtkNew<vtkActor> actor5;
  actor5->SetMapper( mapper5.GetPointer() );
  actor5->GetProperty()->SetRepresentationToWireframe();
  actor5->GetProperty()->SetColor( .7, .7, .7 );

  // Camera
  vtkHyperTreeGrid* ht = htGrid->GetOutput();
  double bd[6];
  ht->GetBounds( bd );
  vtkNew<vtkCamera> camera;
  camera->SetClippingRange( 1., 100. );
  camera->SetFocalPoint( ht->GetCenter() );
  camera->SetPosition( -.8 * bd[1], 2.1 * bd[3], -4.8 * bd[5] );

  // Renderer
  vtkNew<vtkRenderer> renderer;
  renderer->SetActiveCamera( camera.GetPointer() );
  renderer->SetBackground( 1., 1., 1. );
  renderer->AddActor( actor1.GetPointer() );
  renderer->AddActor( actor2.GetPointer() );
  renderer->AddActor( actor3.GetPointer() );
  renderer->AddActor( actor4.GetPointer() );
  renderer->AddActor( actor5.GetPointer() );

  // Render window
  vtkNew<vtkRenderWindow> renWin;
  renWin->AddRenderer( renderer.GetPointer() );
  renWin->SetSize( 300, 300 );
  renWin->SetMultiSamples( 0 );

  // Interactor
  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow( renWin.GetPointer() );

  // Render and test
  renWin->Render();
  
  int retVal = vtkRegressionTestImage( renWin.GetPointer() );
  if ( retVal == vtkRegressionTester::DO_INTERACTOR )
    {
    iren->Start();
    }

  return !retVal;
}

// Created on: 2014-05-22
// Created by: Varvara POSKONINA
// Copyright (c) 2005-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _SelectMgr_BaseFrustum_HeaderFile
#define _SelectMgr_BaseFrustum_HeaderFile

#include <Bnd_Box.hxx>

#include <gp_Pnt.hxx>
#include <gp_Pln.hxx>

#include <Graphic3d_Camera.hxx>
#include <Graphic3d_ClipPlane.hxx>
#include <Graphic3d_SequenceOfHClipPlane.hxx>
#include <Graphic3d_WorldViewProjState.hxx>

#include <TColgp_HArray1OfPnt.hxx>
#include <TColgp_Array1OfPnt2d.hxx>

#include <Select3D_BndBox3d.hxx>
#include <SelectMgr_FrustumBuilder.hxx>
#include <Select3D_TypeOfSensitivity.hxx>
#include <SelectMgr_VectorTypes.hxx>

//! This class is an interface for different types of selecting frustums,
//! defining different selection types, like point, box or polyline
//! selection. It contains signatures of functions for detection of
//! overlap by sensitive entity and initializes some data for building
//! the selecting frustum
class SelectMgr_BaseFrustum : public Standard_Transient
{
public:

  //! Creates new selecting volume with pixel toletance set to 2,
  //! orthographic camera and empty frustum builder
  SelectMgr_BaseFrustum();

  virtual ~SelectMgr_BaseFrustum() {}

  //! Passes camera projection and orientation matrices to builder
  void SetCamera (const Handle(Graphic3d_Camera)& theCamera);

  //! Passes camera projection and orientation matrices to builder
  void SetCamera (const Graphic3d_Mat4d& theProjection,
                  const Graphic3d_Mat4d& theWorldView,
                  const Standard_Integer theIsOrthographic,
                  const Graphic3d_WorldViewProjState& theWVPState = Graphic3d_WorldViewProjState());

  //! @return current camera projection transformation common for all selecting volumes
  const Graphic3d_Mat4d& ProjectionMatrix() const;

  //! @return current camera world view transformation common for all selecting volumes
  const Graphic3d_Mat4d& WorldViewMatrix() const;

  //! @return current camera world view projection transformation state
  const Graphic3d_WorldViewProjState& WorldViewProjState() const;

  void SetPixelTolerance (const Standard_Real theTol);

  void SetWindowSize (const Standard_Integer theWidth, const Standard_Integer theHeight);

  //! Passes viewport parameters to builder
  void SetViewport (const Standard_Real theX,
                    const Standard_Real theY,
                    const Standard_Real theWidth,
                    const Standard_Real theHeight);

  //! Nullifies the builder created in the constructor and copies the pointer given
  void SetBuilder (const Handle(SelectMgr_FrustumBuilder)& theBuilder);


  //! Builds volume according to the point and given pixel tolerance
  virtual void Build (const gp_Pnt2d& /*thePoint*/) {}

  //! Builds volume according to the selected rectangle
  virtual void Build (const gp_Pnt2d& /*theMinPt*/,
                      const gp_Pnt2d& /*theMaxPt*/) {}

  //! Builds volume according to the triangle given
  virtual void Build (const gp_Pnt2d& /*theP1*/,
                      const gp_Pnt2d& /*theP2*/,
                      const gp_Pnt2d& /*theP3*/) {}

  //! Builds selecting volumes set according to polyline points
  virtual void Build (const TColgp_Array1OfPnt2d& /*thePoints*/) {}

  virtual NCollection_Handle<SelectMgr_BaseFrustum> Transform (const gp_Trsf& /*theTrsf*/) { return NULL; }

  //! IMPORTANT: Makes sense only for frustum built on a single point!
  //! Returns a copy of the frustum resized according to the scale factor given
  virtual NCollection_Handle<SelectMgr_BaseFrustum> Scale (const Standard_Real /*theScaleFactor*/) { return NULL; }

  //! SAT intersection test between defined volume and given axis-aligned box
  virtual Standard_Boolean Overlaps (const BVH_Box<Standard_Real, 3>& theBndBox,
                                     Standard_Real& theDepth);

  //! Returns true if selecting volume is overlapped by axis-aligned bounding box
  //! with minimum corner at point theMinPt and maximum at point theMaxPt
  virtual Standard_Boolean Overlaps (const SelectMgr_Vec3& theBoxMin,
                                     const SelectMgr_Vec3& theBoxMax,
                                     Standard_Boolean*     theInside = NULL);

  //! Intersection test between defined volume and given point
  virtual Standard_Boolean Overlaps (const gp_Pnt& thePt,
                                     Standard_Real& theDepth);

  //! SAT intersection test between defined volume and given ordered set of points,
  //! representing line segments. The test may be considered of interior part or
  //! boundary line defined by segments depending on given sensitivity type
  virtual Standard_Boolean Overlaps (const Handle(TColgp_HArray1OfPnt)& theArrayOfPts,
                                     Select3D_TypeOfSensitivity theSensType,
                                     Standard_Real& theDepth);

  //! Checks if line segment overlaps selecting frustum
  virtual Standard_Boolean Overlaps (const gp_Pnt& thePt1,
                                     const gp_Pnt& thePt2,
                                     Standard_Real& theDepth);

  //! SAT intersection test between defined volume and given triangle. The test may
  //! be considered of interior part or boundary line defined by triangle vertices
  //! depending on given sensitivity type
  virtual Standard_Boolean Overlaps (const gp_Pnt& thePt1,
                                     const gp_Pnt& thePt2,
                                     const gp_Pnt& thePt3,
                                     Select3D_TypeOfSensitivity theSensType,
                                     Standard_Real& theDepth);

  //! Measures distance between 3d projection of user-picked
  //! screen point and given point theCOG
  virtual Standard_Real DistToGeometryCenter (const gp_Pnt& theCOG);

  virtual SelectMgr_Vec3 DetectedPoint (const Standard_Real theDepth) const;

  //! Checks if the point of sensitive in which selection was detected belongs
  //! to the region defined by clipping planes
  virtual Standard_Boolean IsClipped (const Graphic3d_SequenceOfHClipPlane& thePlanes,
                                      const Standard_Real theDepth);

  DEFINE_STANDARD_RTTI(SelectMgr_BaseFrustum, Standard_Transient)

protected:
  Standard_Real    myPixelTolerance;      //!< Pixel tolerance
  Standard_Boolean myIsOrthographic;      //!< Defines if current camera is orthographic

  Handle(SelectMgr_FrustumBuilder) myBuilder; //!< A tool implementing methods for volume build
};

#endif // _SelectMgr_BaseFrustum_HeaderFile

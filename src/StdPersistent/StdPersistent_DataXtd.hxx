// Copyright (c) 2015 OPEN CASCADE SAS
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


#ifndef _StdPersistent_DataXtd_HeaderFile
#define _StdPersistent_DataXtd_HeaderFile

#include <StdObjMgt_ContentTypes.hxx>
#include <StdObjMgt_Attribute.hxx>
#include <StdLPersistent_Void.hxx>
#include <StdObject_gp.hxx>

#include <TDataXtd_Shape.hxx>
#include <TDataXtd_Point.hxx>
#include <TDataXtd_Axis.hxx>
#include <TDataXtd_Plane.hxx>
#include <TDataXtd_Placement.hxx>
#include <TDataXtd_Geometry.hxx>
#include <TDataXtd_Position.hxx>


class StdPersistent_DataXtd : private StdObjMgt_ContentTypes
{
  class _void : private StdLPersistent_Void
  {
  public:
    template <class AttribClass>
    struct Instance : instance<AttribClass> {};
  };

public:
  typedef _void::Instance<TDataXtd_Shape>     Shape;
  typedef _void::Instance<TDataXtd_Point>     Point;
  typedef _void::Instance<TDataXtd_Axis>      Axis;
  typedef _void::Instance<TDataXtd_Plane>     Plane;
  typedef _void::Instance<TDataXtd_Placement> Placement;

  class Geometry : public StdObjMgt_Attribute<TDataXtd_Geometry>::
                            Simple <Enum<TDataXtd_GeometryEnum> >
  {
  public:
    //! Import transient attribuite from the persistent data.
    Standard_EXPORT virtual void ImportAttribute();
  };

  class Position : public StdObjMgt_Attribute<TDataXtd_Position>::
                            Simple <StdObject_gp::Object<gp_Pnt> >
  {
  public:
    //! Import transient attribuite from the persistent data.
    Standard_EXPORT virtual void ImportAttribute();
  };
};

#endif
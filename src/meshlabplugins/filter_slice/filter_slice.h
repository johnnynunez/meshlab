/****************************************************************************
* MeshLab                                                           o o     *
* A versatile mesh processing toolbox                             o     o   *
*                                                                _   O  _   *
* Copyright(C) 2008                                                \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/


#ifndef FILTER_SLICE_H
#define FILTER_SLICE_H

#include <QObject>
#include <QAction>
#include <QActionGroup>
#include <QList>
#include <QStringList>

#include <meshlab/meshmodel.h>
#include <meshlab/interfaces.h>

#include <vcg/simplex/edge/base.h>
#include <vcg/complex/edgemesh/base.h>

#include <wrap/io_edgemesh/export_svg.h>

#include <vcg/space/plane3.h>
//#include "svgpro.h"


class MyEdge;
class MyFace;
class MyVertex  : public vcg::VertexSimp2< MyVertex, MyEdge, MyFace,
vcg::vertex::Coord3f,     /* 12b */
vcg::vertex::BitFlags,    /*  4b */
vcg::vertex::EmptyVEAdj
>{
};

class MyEdge    : public vcg::EdgeSimp2<MyVertex,MyEdge,MyFace, vcg::edge::VertexRef> {};


class MyEdgeMesh: public vcg::edg::EdgeMesh< std::vector<MyVertex>, std::vector<MyEdge> > {};

typedef vcg::edg::io::SVGProperties SVGProperties;

class ExtraFilter_SlicePlugin : public QObject, public MeshFilterInterface
{
	Q_OBJECT
	Q_INTERFACES(MeshFilterInterface)

public:
	enum { FP_SINGLE_PLANE, FP_PARALLEL_PLANES, FP_RECURSIVE_SLICE };
	enum { CAP_CW, CAP_CCW };
	ExtraFilter_SlicePlugin();
	~ExtraFilter_SlicePlugin(){};

	virtual QString filterName(FilterIDType filter) const;
	virtual QString filterInfo(FilterIDType filter) const;
	virtual bool autoDialog(QAction *);
	virtual FilterClass getClass(QAction *);
	virtual void initParameterSet(QAction *,MeshModel &/*m*/, RichParameterSet & /*parent*/);
	virtual bool applyFilter(QAction *filter, MeshDocument &m, RichParameterSet & /*parent*/, vcg::CallBackPos * cb) ;
  virtual bool applyFilter(QAction * /* filter */, MeshModel &, RichParameterSet & /*parent*/, vcg::CallBackPos *) { assert(0); return false;} ;
	virtual int getRequirements(QAction *){return MeshModel::MM_FACEFACETOPO | MeshModel::MM_FACEFLAGBORDER | MeshModel::MM_VERTFLAG | MeshModel::MM_VERTMARK | MeshModel::MM_VERTCOORD;}

	static void capHole(MeshModel* orig, MeshModel* dest, int capDir=CAP_CW);
	static void extrude(MeshModel* orig, MeshModel* dest, float eps, vcg::Point3f planeAxis);
private:
	SVGProperties pr;
	void createSlice(MeshModel* orig,MeshModel* dest);
	
	
};

#endif

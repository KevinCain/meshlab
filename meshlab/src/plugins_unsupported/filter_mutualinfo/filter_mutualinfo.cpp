/****************************************************************************
* MeshLab                                                           o o     *
* A versatile mesh processing toolbox                             o     o   *
*                                                                _   O  _   *
* Copyright(C) 2005                                                \/)\/    *
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

#include "filter_mutualinfo.h"
#include <QtScript>
#include "solver.h"
#include "mutual.h"


//#include "shutils.h"

#include <wrap/gl/shot.h>
#include <wrap/gl/camera.h>

// Constructor usually performs only two simple tasks of filling the two lists 
//  - typeList: with all the possible id of the filtering actions
//  - actionList with the corresponding actions. If you want to add icons to your filtering actions you can do here by construction the QActions accordingly

//AlignSet align;


FilterMutualInfoPlugin::FilterMutualInfoPlugin() 
{ 
	typeList << FP_IMAGE_ALIGN;
  
  foreach(FilterIDType tt , types())
	  actionList << new QAction(filterName(tt), this);
}

// ST() must return the very short string describing each filtering action 
// (this string is used also to define the menu entry)
QString FilterMutualInfoPlugin::filterName(FilterIDType filterId) const
{
  switch(filterId) {
		case FP_IMAGE_ALIGN :  return QString("Image Registration: Mutual Information"); 
		default : assert(0); 
	}
  return QString();
}

// Info() must return the longer string describing each filtering action 
// (this string is used in the About plugin dialog)
 QString FilterMutualInfoPlugin::filterInfo(FilterIDType filterId) const
{
  switch(filterId) {
		case FP_IMAGE_ALIGN :  return QString("Register an image on a 3D model using Mutual Information. This filter is an implementation of Corsini et al. 'Image-to-geometry registration: a mutual information method exploiting illumination-related geometric properties', 2009"); 
		default : assert(0); 
	}
	return QString("Unknown Filter");
}

// The FilterClass describes in which generic class of filters it fits. 
// This choice affect the submenu in which each filter will be placed 
// More than a single class can be choosen.
FilterMutualInfoPlugin::FilterClass FilterMutualInfoPlugin::getClass(QAction *a)
{
  switch(ID(a))
	{
		case FP_IMAGE_ALIGN :  return MeshFilterInterface::Camera; 
		default : assert(0); 
	}
	return MeshFilterInterface::Generic;
}

// This function define the needed parameters for each filter. Return true if the filter has some parameters
// it is called every time, so you can set the default value of parameters according to the mesh
// For each parameter you need to define, 
// - the name of the parameter, 
// - the string shown in the dialog 
// - the default value
// - a possibly long string describing the meaning of that parameter (shown as a popup help in the dialog)
void FilterMutualInfoPlugin::initParameterSet(QAction *action,MeshDocument & md, RichParameterSet & parlst) 
{
	QStringList rendList; 
	switch(ID(action))	 {
		case FP_IMAGE_ALIGN :  
			/*parlst.addParam(new RichMesh ("SourceMesh", md.mm(),&md, "Source Mesh",
												"The mesh on which the image must be aligned"));*/
			/*parlst.addParam(new RichRaster ("SourceRaster", md.rm(),&md, "Source Raster",
												"The mesh on which the image must be aligned"));*/
			
			
			rendList.push_back("Combined");
			rendList.push_back("Normal map");
			rendList.push_back("Color per vertex");
			rendList.push_back("Specular");
			rendList.push_back("Silhouette");
			rendList.push_back("Specular combined");

			//rendList.push_back("ABS Curvature");
			parlst.addParam(new RichEnum("RenderingMode", 0, rendList, tr("Rendering mode:"),
                                QString("Rendering mode used for Mutual Information maximization")));
			
			parlst.addParam(new RichShotf  ("Shot", vcg::Shotf(),"Set Shot", "The shot that will be used as a starting position"));
			
			parlst.addParam(new RichBool("Estimate Focal",false,"Estimate focal length","Estimate focal length"));
			parlst.addParam(new RichBool("Fine",true,"Fine Alignment","Fine alignment"));

			parlst.addParam(new RichInt("Num. of Iterations",100,"Max iterations","Maximum number of iterations"));
			parlst.addParam(new RichFloat("Tolerance",0.1,"Tolerance","Threshold to stop convergence"));

			parlst.addParam(new RichFloat("Expected Variance",2.0,"Expected Variance","Expected Variance"));
			parlst.addParam(new RichInt("Background weight",2,"Background weight","Weight of background pixels"));



 		  /*parlst.addParam(new RichBool ("UpdateNormals",
											true,
											"Recompute normals",
											"Toggle the recomputation of the normals after the random displacement.\n\n"
											"If disabled the face normals will remains unchanged resulting in a visually pleasant effect."));
			parlst.addParam(new RichAbsPerc("Displacement",
												m.cm.bbox.Diag()/100.0,0,m.cm.bbox.Diag(),
												"Max displacement",
												"The vertex are displaced of a vector whose norm is bounded by this value"));*/
											break;
											
		default : assert(0); 
	}
}

// The Real Core Function doing the actual mesh processing.
// Move Vertex of a random quantity
bool FilterMutualInfoPlugin::applyFilter(QAction */*filter*/, MeshDocument &md, RichParameterSet & par, vcg::CallBackPos *cb)
{
	Solver solver;
	MutualInfo mutual;
	if (md.rasterList.size()==0)
	{
		 Log(0, "You need a Raster Model to apply this filter!");
		 return false;
	}
	else
		align.image=&md.rm()->currentPlane->image;

	align.mesh=&md.mm()->cm;
	
	solver.optimize_focal=par.getBool("Estimate Focal");
	solver.fine_alignment=par.getBool("Fine");
	solver.variance=par.getFloat("Expected Variance");
	solver.tolerance=par.getFloat("Tolerance");
	solver.maxiter=par.getInt("Num. of Iterations");

	mutual.bweight=par.getInt("Background weight");

	int rendmode= par.getEnum("RenderingMode");
			
			switch(rendmode){ 
				case 0: 
					align.mode=AlignSet::COMBINE;
					break;
				case 1: 
					align.mode=AlignSet::NORMALMAP;
					break;
				case 2: 
					align.mode=AlignSet::COLOR;
					break;
				case 3: 
					align.mode=AlignSet::SPECULAR;
					break;
				case 4: 
					align.mode=AlignSet::SILHOUETTE;
					break;
				case 5: 
					align.mode=AlignSet::SPECAMB;
					break;
				default:
					align.mode=AlignSet::COMBINE;
					break;
			}

	this->glContext->makeCurrent();
	if (this->initGL() == false)
		return false;

	vcg::Point3f *vertices = new vcg::Point3f[align.mesh->vn];
  vcg::Point3f *normals = new vcg::Point3f[align.mesh->vn];
  vcg::Color4b *colors = new vcg::Color4b[align.mesh->vn];
  unsigned int *indices = new unsigned int[align.mesh->fn*3];

  for(int i = 0; i < align.mesh->vn; i++) {
    vertices[i] = align.mesh->vert[i].P();
    normals[i] = align.mesh->vert[i].N();
    colors[i] = align.mesh->vert[i].C();
  }

  for(int i = 0; i < align.mesh->fn; i++) 
    for(int k = 0; k < 3; k++) 
      indices[k+i*3] = align.mesh->face[i].V(k) - &*align.mesh->vert.begin();

  glBindBufferARB(GL_ARRAY_BUFFER_ARB, align.vbo);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, align.mesh->vn*sizeof(vcg::Point3f), 
                  vertices, GL_STATIC_DRAW_ARB);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, align.nbo);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, align.mesh->vn*sizeof(vcg::Point3f), 
                  normals, GL_STATIC_DRAW_ARB);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, align.cbo);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, align.mesh->vn*sizeof(vcg::Color4b), 
                  colors, GL_STATIC_DRAW_ARB);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, align.ibo);
  glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, align.mesh->fn*3*sizeof(unsigned int), 
                  indices, GL_STATIC_DRAW_ARB);
  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);


  // it is safe to delete after copying data to VBO
  delete []vertices;
  delete []normals;
  delete []colors;
  delete []indices;
	
    align.shot=par.getShotf("Shot");
		
	align.shot.Intrinsics.ViewportPx[0]=int((double)align.shot.Intrinsics.ViewportPx[1]*align.image->width()/align.image->height());
	align.shot.Intrinsics.CenterPx[0]=(int)(align.shot.Intrinsics.ViewportPx[0]/2);
	
	if (solver.fine_alignment)
		solver.optimize(&align, &mutual, align.shot);
	else
		solver.iterative(&align, &mutual, align.shot);
	//align.renderScene(align.shot, 3);
	//align.readRender(0);
		
	md.rm()->shot=align.shot;
	float ratio=(float)md.rm()->currentPlane->image.height()/(float)align.shot.Intrinsics.ViewportPx[1];
	md.rm()->shot.Intrinsics.ViewportPx[0]=md.rm()->currentPlane->image.width();
	md.rm()->shot.Intrinsics.ViewportPx[1]=md.rm()->currentPlane->image.height();
	md.rm()->shot.Intrinsics.PixelSizeMm[1]/=ratio;
	md.rm()->shot.Intrinsics.PixelSizeMm[0]/=ratio;
	md.rm()->shot.Intrinsics.CenterPx[0]=(int)((float)md.rm()->shot.Intrinsics.ViewportPx[0]/2.0);
	md.rm()->shot.Intrinsics.CenterPx[1]=(int)((float)md.rm()->shot.Intrinsics.ViewportPx[1]/2.0);

	this->glContext->doneCurrent();
	//emit md.rasterSetChanged();
	return true;
}

bool FilterMutualInfoPlugin::initGL()
{
  GLenum err = glewInit();
  Log(0, "GL Initialization");
  if (GLEW_OK != err) {
    Log(0, "GLEW initialization error!");
    return false;
  }

  if (!glewIsSupported("GL_EXT_framebuffer_object")) {
    Log(0, "Graphics hardware does not support FBOs");
    return false;
  }
  if (!glewIsSupported("GL_ARB_vertex_shader") || !glewIsSupported("GL_ARB_fragment_shader") ||
      !glewIsSupported("GL_ARB_shader_objects") || !glewIsSupported("GL_ARB_shading_language")) {
    //QMessageBox::warning(this, "Danger, Will Robinson!",
//                         "Graphics hardware does not fully support Shaders");
  }

  if (!glewIsSupported("GL_ARB_texture_non_power_of_two")) {
    Log(0,"Graphics hardware does not support non-power-of-two textures");
    return false;
  }
  if (!glewIsSupported("GL_ARB_vertex_buffer_object")) {
    Log(0, "Graphics hardware does not support vertex buffer objects");
    return false;
  }

  glEnable(GL_NORMALIZE);
  glDepthRange (0.0, 1.0);

  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_POLYGON_SMOOTH);
  glShadeModel(GL_SMOOTH);
  glDisable(GL_POLYGON_SMOOTH);

  //AlignSet &align = Autoreg::instance().align;
  align.initializeGL();
  align.resize(800);
  //assert(glGetError() == 0);

  Log(0, "GL Initialization done");
  return true;

}

QString FilterMutualInfoPlugin::filterScriptFunctionName( FilterIDType filterID )
{
	switch(filterID) {
		case FP_IMAGE_ALIGN :  return QString("imagealignment"); 
		default : assert(0); 
	}
	return QString();
}

Q_EXPORT_PLUGIN(FilterMutualInfoPlugin)

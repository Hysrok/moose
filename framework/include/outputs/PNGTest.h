//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

// Forward declarations
class PNGTest;

template <>
InputParameters validParams<PNGTest>();

// MOOSE includes
#include "Output.h"
class PNGTest : public Output
{
public:
  //Basic constructor.  Takes parameters passed in to create a PNGCreator object.
  PNGTest(const InputParameters & parameters);

  // Function to create the mesh_function
  void makeMeshFunc();

  // Function to populate values to the variables used for scaling
  void calculateRescalingValues();

  // Function that creates the PNG
  void makePNG();

  // Called to run the functions in this class.
  virtual void output(const ExecFlagType & /*type*/);

  // Variable to determine the size, or resolution, of the image.
  Real resolution;

  // Name of file to which the PNG will be written.
  std::string PNGFile;

  // Specific test step to create the image for.
  Real picked;

  //deprecated previous way of setting up the bounds
  Real xdist;
  Real ydist;

  // Way to specify color vs grayscale image creation.
  bool inColor;

  // Way to track the number test step number and the associated png, if created.
  Real numpng = 0;

  //deprecated increment string value.
  std::string appe = "one";

  /// The XDA or ExodusII file that is being read---------propaply won't use in this iteration.
//  std::string _mesh_file;

  /// Pointer the libMesh::MeshFunction object that the read data is stored
  std::unique_ptr<MeshFunction> _mesh_function;

  // The boundaries of the image.
  BoundingBox box;

  // Values used for rescaling the image.
  Real scalingMin;
  Real scalingMax;
  Real shiftValue;

};

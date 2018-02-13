/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkModifiedButterflyTriangleEdgeCellSubdivisionQuadEdgeMeshFilter.h"
#include "itkLinearTriangleEdgeCellSubdivisionQuadEdgeMeshFilter.h"
#include "itkLoopTriangleEdgeCellSubdivisionQuadEdgeMeshFilter.h"
#include "itkConditionalSubdivisionQuadEdgeMeshFilter.h"
#include "itkEdgeLengthTriangleEdgeCellSubdivisionCriterion.h"
#include "itkQuadEdgeMeshParamMatrixCoefficients.h"
#include "itkSmoothingQuadEdgeMeshFilter.h"
#include "itkMeshFileReader.h"
#include "itkMeshFileWriter.h"

template< typename TTriangleEdgeCellSubdivisionFilter >
int CriterionTriangleEdgeCellSubdivisionQuadEdgeMeshFilterTest( int argc, char *argv[] )
{

  using TriangleEdgeCellSubdivisionFilterType = TTriangleEdgeCellSubdivisionFilter;
  using TriangleEdgeCellSubdivisionFilterPointer = typename TriangleEdgeCellSubdivisionFilterType::Pointer;
  using InputMeshType = typename TriangleEdgeCellSubdivisionFilterType::InputMeshType;
  using OutputMeshType = typename TriangleEdgeCellSubdivisionFilterType::OutputMeshType;

  using CriterionType = itk::EdgeLengthTriangleEdgeCellSubdivisionCriterion< typename TriangleEdgeCellSubdivisionFilterType::SubdivisionFilterType >;
  using CriterionPointer = typename CriterionType::Pointer;

  using ReaderType = itk::MeshFileReader< InputMeshType >;
  using WriterType = itk::MeshFileWriter< OutputMeshType >;

  typename ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  try
    {
    reader->Update();
    }
  catch ( itk::ExceptionObject & exp )
    {
    std::cerr << "Exception thrown while reading the input file " << std::endl;
    std::cerr << exp << std::endl;
    return EXIT_FAILURE;
    }

  TriangleEdgeCellSubdivisionFilterPointer subdivision = TriangleEdgeCellSubdivisionFilterType::New();
  CriterionPointer criterion = CriterionType::New();
  criterion->SetMaximumLength(1.0);
  if ( argc >= 5 )
    {
    float length = std::atof( argv[4] );
    criterion->SetMaximumLength( length );
    }

  subdivision->SetSubdivisionCriterion( criterion.GetPointer() );
  subdivision->SetInput( reader->GetOutput() );
  subdivision->Update();
  typename OutputMeshType::Pointer output = subdivision->GetOutput();

  bool smoothing = false;
  if ( argc >= 6 )
  {
  smoothing = true;
  }

  if ( smoothing )
    {
    using OutputMeshSmoothingFilterType = itk::SmoothingQuadEdgeMeshFilter< OutputMeshType, OutputMeshType >;
    using OnesMatrixCoefficientsType = itk::OnesMatrixCoefficients< OutputMeshType >;

    OnesMatrixCoefficientsType coef;
    typename OutputMeshSmoothingFilterType::Pointer meshSmoothingFilter = OutputMeshSmoothingFilterType::New();
    meshSmoothingFilter->SetInput( output );
    meshSmoothingFilter->SetCoefficientsMethod(&coef);
    meshSmoothingFilter->SetDelaunayConforming(1);
    meshSmoothingFilter->SetNumberOfIterations(1);
    meshSmoothingFilter->Update();

    output->Graft( meshSmoothingFilter->GetOutput() );
    }

  typename WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(argv[2]);
  writer->SetInput( output );

  try
    {
    writer->Update();
    }
  catch ( itk::ExceptionObject & exp )
    {
    std::cerr << "Exception thrown while writting the output file " << std::endl;
    std::cerr << exp << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

int itkCriterionTriangleEdgeCellSubdivisionQuadEdgeMeshFilterTest( int argc, char *argv[] )
{
  if ( argc < 3 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputMeshFile  outputMeshFile subdivisionType area" << std::endl;
    std::cerr << " 0 : ModifiedButterfly " << std::endl;
    std::cerr << " 1 : Linear " << std::endl;
    std::cerr << " 2 : Loop " << std::endl;
    return EXIT_FAILURE;
    }

  using MeshPixelType = float;
  const unsigned int Dimension = 3;

  using InputMeshType = itk::QuadEdgeMesh< MeshPixelType, Dimension >;
  using OutputMeshType = itk::QuadEdgeMesh< MeshPixelType, Dimension >;

  using ModifiedButterflySubdivisionFilterType = itk::ModifiedButterflyTriangleEdgeCellSubdivisionQuadEdgeMeshFilter< OutputMeshType, OutputMeshType >;
  using LinearSubdivisionFilterType = itk::LinearTriangleEdgeCellSubdivisionQuadEdgeMeshFilter< OutputMeshType, OutputMeshType >;
  using LoopSubdivisionFilterType = itk::LoopTriangleEdgeCellSubdivisionQuadEdgeMeshFilter< OutputMeshType, OutputMeshType >;

  using ConditionalModifiedButterflySubdivisionFilterType = itk::ConditionalSubdivisionQuadEdgeMeshFilter< InputMeshType, ModifiedButterflySubdivisionFilterType >;
  using ConditionalLinearSubdivisionFilterType = itk::ConditionalSubdivisionQuadEdgeMeshFilter< InputMeshType, LinearSubdivisionFilterType >;
  using ConditionalLoopSubdivisionFilterType = itk::ConditionalSubdivisionQuadEdgeMeshFilter< InputMeshType, LoopSubdivisionFilterType >;

  if ( argc >= 4 )
    {
    int type = std::atoi(argv[3]);

    switch ( type )
      {
      case 0:
        return CriterionTriangleEdgeCellSubdivisionQuadEdgeMeshFilterTest< ConditionalModifiedButterflySubdivisionFilterType >( argc, argv );
      case 1:
        return CriterionTriangleEdgeCellSubdivisionQuadEdgeMeshFilterTest< ConditionalLinearSubdivisionFilterType >( argc, argv );
      case 2:
        return CriterionTriangleEdgeCellSubdivisionQuadEdgeMeshFilterTest< ConditionalLoopSubdivisionFilterType >( argc, argv );
      default:
        std::cerr << "Invalid subdivision type : " << type << std::endl;
        return EXIT_FAILURE;
      }
    }
  else
    {
    std::cerr << "You must have subdivision type " << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

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

#ifndef itkEdgeLengthTriangleEdgeCellSubdivisionCriterion_h
#define itkEdgeLengthTriangleEdgeCellSubdivisionCriterion_h

#include "itkQuadEdgeMeshSubdivisionCriterion.h"
#include "itkObjectFactory.h"
#include "itkNumericTraits.h"


namespace itk
{
/**
 *\class EdgeLengthTriangleEdgeCellSubdivisionCriterion
 *\brief
 *\ingroup SubdivisionQuadEdgeMeshFilter
 */
template< typename TSubdivisionFilter >
class EdgeLengthTriangleEdgeCellSubdivisionCriterion : public QuadEdgeMeshSubdivisionCriterion< TSubdivisionFilter >
{
public:
  typedef EdgeLengthTriangleEdgeCellSubdivisionCriterion            Self;
  typedef QuadEdgeMeshSubdivisionCriterion< TSubdivisionFilter >    Superclass;
  typedef SmartPointer< Self >                                      Pointer;
  typedef SmartPointer< const Self >                                ConstPointer;

  typedef typename Superclass::MeshType                             MeshType;
  typedef typename Superclass::MeshPointer                          MeshPointer;
  typedef typename Superclass::MeshConstPointer                     MeshConstPointer;
  typedef typename Superclass::PointsContainerPointer               PointsContainerPointer;
  typedef typename Superclass::PointsContainerConstIterator         PointsContainerConstIterator;
  typedef typename Superclass::PointsContainerIterator              PointsContainerIterator;
  typedef typename Superclass::CellsContainer                       CellsContainer;
  typedef typename Superclass::CellsContainerPointer                CellsContainerPointer;
  typedef typename Superclass::CellsContainerIterator               CellsContainerIterator;
  typedef typename Superclass::CellsContainerConstIterator          CellsContainerConstIterator;
  typedef typename Superclass::PointType                            PointType;
  typedef typename Superclass::CoordRepType                         CoordRepType;
  typedef typename Superclass::PointIdentifier                      PointIdentifier;
  typedef typename Superclass::CellIdentifier                       CellIdentifier;
  typedef typename Superclass::CellType                             CellType;
  typedef typename Superclass::QEType                               QEType;
  typedef typename Superclass::PointIdIterator                      PointIdIterator;
  typedef typename Superclass::SubdivisionCellContainer             SubdivisionCellContainer;

  /** Run-time type information (and related methods).   */
  itkTypeMacro( EdgeLengthTriangleEdgeCellSubdivisionCriterion, QuadEdgeMeshSubdivisionCriterion );
  itkNewMacro( Self );

  void Compute( MeshType * mesh, SubdivisionCellContainer & edgeList ) ITK_OVERRIDE;

  itkGetConstMacro(MaximumLength, CoordRepType);
  itkSetMacro(MaximumLength, CoordRepType);

protected:
  EdgeLengthTriangleEdgeCellSubdivisionCriterion(){ m_MaximumLength = NumericTraits< CoordRepType >::max(); }
  ~EdgeLengthTriangleEdgeCellSubdivisionCriterion() ITK_OVERRIDE{}

private:
  CoordRepType m_MaximumLength;
};

}
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkEdgeLengthTriangleEdgeCellSubdivisionCriterion.hxx"
#endif

#endif

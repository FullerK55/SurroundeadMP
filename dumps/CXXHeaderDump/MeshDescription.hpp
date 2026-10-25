#ifndef UE4SS_SDK_MeshDescription_HPP
#define UE4SS_SDK_MeshDescription_HPP

#include "MeshDescription_enums.hpp"

struct FBoneID : public FElementID
{
}; // Size: 0x4

struct FEdgeID : public FElementID
{
}; // Size: 0x4

struct FElementID
{
    int32 IDValue;                                                                    // 0x0000 (size: 0x4)

}; // Size: 0x4

struct FPolygonGroupID : public FElementID
{
}; // Size: 0x4

struct FPolygonID : public FElementID
{
}; // Size: 0x4

struct FTriangleID : public FElementID
{
}; // Size: 0x4

struct FUVID : public FElementID
{
}; // Size: 0x4

struct FVertexID : public FElementID
{
}; // Size: 0x4

struct FVertexInstanceID : public FElementID
{
}; // Size: 0x4

class UMeshDescriptionBase : public UObject
{

    void SetVertexPosition(FVertexID VertexID, const FVector& Position);
    void SetPolygonVertexInstances(FPolygonID PolygonID, const TArray<FVertexInstanceID>& VertexInstanceIDs);
    void SetPolygonPolygonGroup(FPolygonID PolygonID, FPolygonGroupID PolygonGroupID);
    void ReversePolygonFacing(FPolygonID PolygonID);
    void ReserveNewVertices(int32 NumberOfNewVertices);
    void ReserveNewVertexInstances(int32 NumberOfNewVertexInstances);
    void ReserveNewTriangles(int32 NumberOfNewTriangles);
    void ReserveNewPolygons(const int32 NumberOfNewPolygons);
    void ReserveNewPolygonGroups(int32 NumberOfNewPolygonGroups);
    void ReserveNewEdges(int32 NumberOfNewEdges);
    void IsVertexValid(FVertexID VertexID);
    void IsVertexOrphaned(FVertexID VertexID);
    void IsVertexInstanceValid(FVertexInstanceID VertexInstanceID);
    void IsTriangleValid(const FTriangleID TriangleID);
    void IsTrianglePartOfNgon(FTriangleID TriangleID);
    void IsPolygonValid(FPolygonID PolygonID);
    void IsPolygonGroupValid(FPolygonGroupID PolygonGroupID);
    void IsEmpty();
    void IsEdgeValid(FEdgeID EdgeID);
    void IsEdgeInternalToPolygon(FEdgeID EdgeID, FPolygonID PolygonID);
    void IsEdgeInternal(FEdgeID EdgeID);
    void GetVertexVertexInstances(FVertexID VertexID, TArray<FVertexInstanceID>& OutVertexInstanceIDs);
    void GetVertexPosition(FVertexID VertexID);
    void GetVertexPairEdge(FVertexID VertexID0, FVertexID VertexID1);
    void GetVertexInstanceVertex(FVertexInstanceID VertexInstanceID);
    void GetVertexInstancePairEdge(FVertexInstanceID VertexInstanceID0, FVertexInstanceID VertexInstanceID1);
    void GetVertexInstanceForTriangleVertex(FTriangleID TriangleID, FVertexID VertexID);
    void GetVertexInstanceForPolygonVertex(FPolygonID PolygonID, FVertexID VertexID);
    void GetVertexInstanceCount();
    void GetVertexInstanceConnectedTriangles(FVertexInstanceID VertexInstanceID, TArray<FTriangleID>& OutConnectedTriangleIDs);
    void GetVertexInstanceConnectedPolygons(FVertexInstanceID VertexInstanceID, TArray<FPolygonID>& OutConnectedPolygonIDs);
    void GetVertexCount();
    void GetVertexConnectedTriangles(FVertexID VertexID, TArray<FTriangleID>& OutConnectedTriangleIDs);
    void GetVertexConnectedPolygons(FVertexID VertexID, TArray<FPolygonID>& OutConnectedPolygonIDs);
    void GetVertexConnectedEdges(FVertexID VertexID, TArray<FEdgeID>& OutEdgeIDs);
    void GetVertexAdjacentVertices(FVertexID VertexID, TArray<FVertexID>& OutAdjacentVertexIDs);
    void GetTriangleVertices(FTriangleID TriangleID, TArray<FVertexID>& OutVertexIDs);
    void GetTriangleVertexInstances(FTriangleID TriangleID, TArray<FVertexInstanceID>& OutVertexInstanceIDs);
    void GetTriangleVertexInstance(FTriangleID TriangleID, int32 Index);
    void GetTrianglePolygonGroup(FTriangleID TriangleID);
    void GetTrianglePolygon(FTriangleID TriangleID);
    void GetTriangleEdges(FTriangleID TriangleID, TArray<FEdgeID>& OutEdgeIDs);
    void GetTriangleCount();
    void GetTriangleAdjacentTriangles(FTriangleID TriangleID, TArray<FTriangleID>& OutTriangleIDs);
    void GetPolygonVertices(FPolygonID PolygonID, TArray<FVertexID>& OutVertexIDs);
    void GetPolygonVertexInstances(FPolygonID PolygonID, TArray<FVertexInstanceID>& OutVertexInstanceIDs);
    void GetPolygonTriangles(FPolygonID PolygonID, TArray<FTriangleID>& OutTriangleIDs);
    void GetPolygonPolygonGroup(FPolygonID PolygonID);
    void GetPolygonPerimeterEdges(FPolygonID PolygonID, TArray<FEdgeID>& OutEdgeIDs);
    void GetPolygonInternalEdges(FPolygonID PolygonID, TArray<FEdgeID>& OutEdgeIDs);
    void GetPolygonGroupPolygons(FPolygonGroupID PolygonGroupID, TArray<FPolygonID>& OutPolygonIDs);
    void GetPolygonGroupCount();
    void GetPolygonCount();
    void GetPolygonAdjacentPolygons(FPolygonID PolygonID, TArray<FPolygonID>& OutPolygonIDs);
    void GetNumVertexVertexInstances(FVertexID VertexID);
    void GetNumVertexInstanceConnectedTriangles(FVertexInstanceID VertexInstanceID);
    void GetNumVertexInstanceConnectedPolygons(FVertexInstanceID VertexInstanceID);
    void GetNumVertexConnectedTriangles(FVertexID VertexID);
    void GetNumVertexConnectedPolygons(FVertexID VertexID);
    void GetNumVertexConnectedEdges(FVertexID VertexID);
    void GetNumPolygonVertices(FPolygonID PolygonID);
    void GetNumPolygonTriangles(FPolygonID PolygonID);
    void GetNumPolygonInternalEdges(FPolygonID PolygonID);
    void GetNumPolygonGroupPolygons(FPolygonGroupID PolygonGroupID);
    void GetNumEdgeConnectedTriangles(FEdgeID EdgeID);
    void GetNumEdgeConnectedPolygons(FEdgeID EdgeID);
    void GetEdgeVertices(const FEdgeID EdgeID, TArray<FVertexID>& OutVertexIDs);
    void GetEdgeVertex(FEdgeID EdgeID, int32 VertexNumber);
    void GetEdgeCount();
    void GetEdgeConnectedTriangles(FEdgeID EdgeID, TArray<FTriangleID>& OutConnectedTriangleIDs);
    void GetEdgeConnectedPolygons(FEdgeID EdgeID, TArray<FPolygonID>& OutConnectedPolygonIDs);
    void Empty();
    void DeleteVertexInstance(FVertexInstanceID VertexInstanceID, TArray<FVertexID>& OrphanedVertices);
    void DeleteVertex(FVertexID VertexID);
    void DeleteTriangle(FTriangleID TriangleID, TArray<FEdgeID>& OrphanedEdges, TArray<FVertexInstanceID>& OrphanedVertexInstances, TArray<FPolygonGroupID>& OrphanedPolygonGroupsPtr);
    void DeletePolygonGroup(FPolygonGroupID PolygonGroupID);
    void DeletePolygon(FPolygonID PolygonID, TArray<FEdgeID>& OrphanedEdges, TArray<FVertexInstanceID>& OrphanedVertexInstances, TArray<FPolygonGroupID>& OrphanedPolygonGroups);
    void DeleteEdge(FEdgeID EdgeID, TArray<FVertexID>& OrphanedVertices);
    void CreateVertexWithID(FVertexID VertexID);
    void CreateVertexInstanceWithID(FVertexInstanceID VertexInstanceID, FVertexID VertexID);
    void CreateVertexInstance(FVertexID VertexID);
    void CreateVertex();
    void CreateTriangleWithID(FTriangleID TriangleID, FPolygonGroupID PolygonGroupID, const TArray<FVertexInstanceID>& VertexInstanceIDs, TArray<FEdgeID>& NewEdgeIDs);
    void CreateTriangle(FPolygonGroupID PolygonGroupID, const TArray<FVertexInstanceID>& VertexInstanceIDs, TArray<FEdgeID>& NewEdgeIDs);
    void CreatePolygonWithID(FPolygonID PolygonID, FPolygonGroupID PolygonGroupID, TArray<FVertexInstanceID>& VertexInstanceIDs, TArray<FEdgeID>& NewEdgeIDs);
    void CreatePolygonGroupWithID(FPolygonGroupID PolygonGroupID);
    void CreatePolygonGroup();
    void CreatePolygon(FPolygonGroupID PolygonGroupID, TArray<FVertexInstanceID>& VertexInstanceIDs, TArray<FEdgeID>& NewEdgeIDs);
    void CreateEdgeWithID(FEdgeID EdgeID, FVertexID VertexID0, FVertexID VertexID1);
    void CreateEdge(FVertexID VertexID0, FVertexID VertexID1);
    void ComputePolygonTriangulation(FPolygonID PolygonID);
}; // Size: 0x2F0

class UMeshDescriptionBaseBulkData : public UObject
{
}; // Size: 0x28

#endif

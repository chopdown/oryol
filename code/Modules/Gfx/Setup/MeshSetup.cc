//------------------------------------------------------------------------------
//  MeshSetup.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "MeshSetup.h"

namespace Oryol {

//------------------------------------------------------------------------------
MeshSetup::MeshSetup() :
VertexUsage(Usage::InvalidUsage),
IndexUsage(Usage::InvalidUsage),
NumVertices(0),
NumIndices(0),
IndicesType(IndexType::None),
Locator(Locator::NonShared()),
StreamVertexOffset(0),
StreamIndexOffset(InvalidIndex),
numPrimGroups(0),
setupFromFile(false),
setupFromStream(false),
setupEmpty(false),
setupFullScreenQuad(false) {
    // empty
}

//------------------------------------------------------------------------------
MeshSetup
MeshSetup::FromFile(const class Locator& loc, Id placeholder) {
    MeshSetup setup;
    setup.VertexUsage = Usage::Immutable;
    setup.IndexUsage = Usage::Immutable;
    setup.Locator = loc;
    setup.Placeholder = placeholder;
    setup.setupFromFile = true;
    return setup;
}

//------------------------------------------------------------------------------
MeshSetup
MeshSetup::FromStream(Usage::Code vbUsage, Usage::Code ibUsage) {
    MeshSetup setup;
    setup.VertexUsage = vbUsage;
    setup.IndexUsage = ibUsage;
    setup.setupFromStream = true;
    return setup;
}

//------------------------------------------------------------------------------
MeshSetup
MeshSetup::FromStream(const MeshSetup& blueprint) {
    MeshSetup setup(blueprint);
    setup.setupFromStream = true;
    return setup;
}

//------------------------------------------------------------------------------
MeshSetup
MeshSetup::Empty(int32 numVertices,
                 Usage::Code vertexUsage,
                 IndexType::Code indexType,
                 int32 numIndices,
                 Usage::Code indexUsage) {
    
    o_assert_dbg(numVertices > 0);
    
    MeshSetup setup;
    setup.setupEmpty = true;
    setup.VertexUsage = vertexUsage;
    setup.IndexUsage = indexUsage;
    setup.NumVertices = numVertices;
    setup.NumIndices = numIndices;
    setup.IndicesType = indexType;
    return setup;
}

//------------------------------------------------------------------------------
MeshSetup
MeshSetup::FullScreenQuad() {
    MeshSetup setup;
    setup.setupFullScreenQuad = true;
    return setup;
}

//------------------------------------------------------------------------------
bool
MeshSetup::ShouldSetupFromFile() const {
    return this->setupFromFile;
}

//------------------------------------------------------------------------------
bool
MeshSetup::ShouldSetupFromStream() const {
    return this->setupFromStream;
}

//------------------------------------------------------------------------------
bool
MeshSetup::ShouldSetupEmpty() const {
    return this->setupEmpty;
}

//------------------------------------------------------------------------------
bool
MeshSetup::ShouldSetupFullScreenQuad() const {
    return this->setupFullScreenQuad;
}

//------------------------------------------------------------------------------
void
MeshSetup::AddPrimitiveGroup(const class PrimitiveGroup& primGroup) {
    o_assert(this->setupEmpty || this->setupFromStream);
    o_assert(this->numPrimGroups < MaxNumPrimGroups);
    this->primGroups[this->numPrimGroups++] = primGroup;
}

//------------------------------------------------------------------------------
int32
MeshSetup::NumPrimitiveGroups() const {
    return this->numPrimGroups;
}

//------------------------------------------------------------------------------
const class PrimitiveGroup&
MeshSetup::PrimitiveGroup(int32 index) const {
    o_assert_range(index, MaxNumPrimGroups);
    return this->primGroups[index];
}

} // namespace Oryol
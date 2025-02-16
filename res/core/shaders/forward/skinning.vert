
vec4 _skinnedPosition;

void skinPosition(float blendWeight, int matrixIndex)
{
    vec4 tmp;
    tmp.x = dot(a_position, u_matrixPalette[matrixIndex]);
    tmp.y = dot(a_position, u_matrixPalette[matrixIndex + 1]);
    tmp.z = dot(a_position, u_matrixPalette[matrixIndex + 2]);
    tmp.w = a_position.w;
    _skinnedPosition += blendWeight * tmp;
}

vec4 getPosition()
{
    _skinnedPosition = vec4(0.0);
    float blendWeight = a_weight[0];
    int matrixIndex = int (a_indices[0]) * 3;
    skinPosition(blendWeight, matrixIndex);
    blendWeight = a_weight[1];
    matrixIndex = int(a_indices[1]) * 3;
    skinPosition(blendWeight, matrixIndex);
    blendWeight = a_weight[2];
    matrixIndex = int(a_indices[2]) * 3;
    skinPosition(blendWeight, matrixIndex);
    blendWeight = a_weight[3];
    matrixIndex = int(a_indices[3]) * 3;
    skinPosition(blendWeight, matrixIndex);
    return _skinnedPosition;    
}

#if defined(LIGHTING)

vec3 _skinnedNormal;

void skinTangentSpaceVector(vec3 vector, float blendWeight, int matrixIndex)
{
    vec3 tmp;
    tmp.x = dot(vector, u_matrixPalette[matrixIndex].xyz);
    tmp.y = dot(vector, u_matrixPalette[matrixIndex + 1].xyz);
    tmp.z = dot(vector, u_matrixPalette[matrixIndex + 2].xyz);
    _skinnedNormal += blendWeight * tmp;
}

vec3 getTangentSpaceVector(vec3 vector)
{
    _skinnedNormal = vec3(0.0);
    // Transform normal to view space using matrix palette with four matrices used to transform a vertex.
    float blendWeight = a_weight[0];
    int matrixIndex = int (a_indices[0]) * 3;
    skinTangentSpaceVector(vector, blendWeight, matrixIndex);
    blendWeight = a_weight[1];
    matrixIndex = int(a_indices[1]) * 3;
    skinTangentSpaceVector(vector, blendWeight, matrixIndex);
    blendWeight = a_weight[2];
    matrixIndex = int(a_indices[2]) * 3;
    skinTangentSpaceVector(vector, blendWeight, matrixIndex);
    blendWeight = a_weight[3];
    matrixIndex = int(a_indices[3]) * 3;
    skinTangentSpaceVector(vector, blendWeight, matrixIndex);
    return _skinnedNormal;
}

vec3 getNormal()
{
    return getTangentSpaceVector(a_normal);
}

#if defined(BUMPED)

vec3 getTangent()
{
    return getTangentSpaceVector(a_tangent);
}

vec3 getBinormal()
{
    return getTangentSpaceVector(a_bitangent);
}

#endif

#endif


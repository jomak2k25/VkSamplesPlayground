/* Copyright (c) 2025, Sascha Willems
 *
 * SPDX-License-Identifier: MIT
 *
 */

struct Payload
{
    float3 hitValue;
    uint payloadSeed;
    bool shadowed;
};

struct GeometryNode {
    ConstBufferPointer<float4> vertices;
    ConstBufferPointer<uint> indices;
    int textureIndexBaseColor;
    int textureIndexOcclusion;
};

[[vk::binding(0, 0)]] RaytracingAccelerationStructure accelStruct;
[[vk::binding(1, 0)]] Texture2D<float4> positionsIn;
[[vk::binding(2, 0)]] Texture2D<float4> normalsIn;
[[vk::binding(3, 0)]] RWTexture2D<float> aoResult;


struct Attributes
{
    float2 bary;
};

[shader("raygeneration")]
void raygenerationMain()
{
    
}

[shader("closesthit")]
void closesthitMain(inout Payload payload, in Attributes attribs)
{

}

[shader("anyhit")]
void anyhitMain(inout Payload payload, in Attributes attribs)
{
}

[shader("miss")]
void missMain(inout Payload payload)
{
}
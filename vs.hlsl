struct VSOUT
{
    float4 out_position : SV_POSITION;
    float4 out_color : COLOR;
};

VSOUT main(float3 position : POSITION, float3 color : COLOR)
{
    VSOUT _out;
    _out.out_position = float4(position, 1.0f);
    _out.out_color = float4(color, 1.0f);

    return _out;
}
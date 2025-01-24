#include "Object3d.hlsli"

struct Material
{
    float32_t4 color;              // マテリアルの基本色
    int32_t enableLighting;        // ライティングの有効化フラグ
    float32_t4x4 uvTransform;      // UV変換マトリックス
    float32_t shininess;           // 鏡面反射の鋭さ（ハイライトの強度）
};

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0; // ピクセルシェーダーの出力色
};

struct DirectionalLight
{
    float32_t4 color;              // ライトの色
    float32_t3 direction;          // ライトの方向ベクトル
    float intensity;               // ライトの強度
};

struct Camera
{
    float32_t3 worldPosition;      // カメラのワールド座標
};

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
ConstantBuffer<Camera> gCamera : register(b2);

Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

PixelShaderOutput main(VertexShaderOutput input)
{
    // UV変換
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    PixelShaderOutput output;
    
    // ライティングが有効な場合
    if (gMaterial.enableLighting != 0)
    {
        // ライトと法線の角度を計算
        float NdotL = dot(normalize(input.normal), normalize(-gDirectionalLight.direction));
        float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
        
        // カメラへの方向ベクトル
        float32_t3 toEye = normalize(gCamera.worldPosition - input.worldPostion);
        
        // Phongモデルの鏡面反射計算
        //float32_t3 reflectLight = reflect(normalize(-gDirectionalLight.direction), normalize(input.normal));
        //float RdotE = dot(reflectLight, toEye);
        //float specularPow = pow(saturate(RdotE), gMaterial.shininess);
        
        // Blinn-Phongモデル用の鏡面反射計算
        float32_t3 halfVector = normalize(-gDirectionalLight.direction + toEye);
        float NDotH = dot(normalize(input.normal), halfVector);
        float specularPow = pow(saturate(NDotH), gMaterial.shininess);
        
        // 拡散反射
        float32_t3 diffuse = 
        gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
        // 鏡面反射
        float32_t3 specular =
        gDirectionalLight.color.rgb * gDirectionalLight.intensity * specularPow * float32_t3(1.0f, 1.0f, 1.0f);
        // 拡散反射+鏡面反射
        output.color.rgb = diffuse + specular;
        // アルファは今まで通り
        output.color.a = gMaterial.color.a * textureColor.a;
    }
    else
    {
        // ライティング無効時は単純にテクスチャとマテリアルの色を乗算
        output.color = gMaterial.color * textureColor;
    }
    
    return output;
}
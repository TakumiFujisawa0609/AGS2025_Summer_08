//#include <DxLib.h>
//#include "../../Utility/AsoUtility.h"
//#include "../Player.h"
//#include "ItemLight.h"
//
//ItemLight::ItemLight()
//{
//}
//
//ItemLight::~ItemLight()
//{
//    if (lightHandle_ != -1)
//    {
//        DeleteLightHandle(lightHandle_);
//    }
//}
//
//void ItemLight::Update()
//{
//    if (!isActive_) return;  // ← 追加
//    if (lightHandle_ != -1)
//    {
//        SetLightPositionHandle(lightHandle_, VAdd(pos_, VGet(0, 150.0f, 0)));
//    }
//}
//
//void ItemLight::Draw()
//{
//    if (!isActive_) return;  // ← これを追加
//    MV1DrawModel(modelId_);
//}
//
//VECTOR ItemLight::GetLPos()
//{
//    return pos_;
//}
//
//void ItemLight::SetParam()
//{
//    scale_ = { 0.13f, 0.13f, 0.13f };
//    // 向き設定
//    MV1SetRotationXYZ(modelId_, { 0,  AsoUtility::Deg2RadF(-90.0f), 0 });
//
//    MV1SetMaterialEmiColor(modelId_, 0, GetColorF(2.6f, 2.6f, 2.6f, 1.0f));
//    MV1SetMaterialEmiColor(modelId_, 1, GetColorF(1.6f, 1.6f, 1.6f, 1.0f));
//
//    // ポイントライト作成
//    //lightHandle_ = CreatePointLightHandle(
//    //    VAdd(pos_, VGet(0, 50.0f, 0)),
//    //    300.0f,   // 範囲
//    //    1.0f,     // Atten0
//    //    0.05f,    // Atten1
//    //    0.01f     // Atten2
//    //);
//
//    //// 光の色（明るめに）
//    //SetLightDifColorHandle(lightHandle_, GetColorF(1.0f, 0.9f, 0.7f, 1.0f));
//}
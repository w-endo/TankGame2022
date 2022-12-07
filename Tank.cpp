#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
Tank::Tank(GameObject* parent)
    :GameObject(parent, "Tank"), hModel_(-1)
{
}

//デストラクタ
Tank::~Tank()
{
}

//初期化
void Tank::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("TankBody.fbx");
    assert(hModel_ >= 0);
}

//更新
void Tank::Update()
{
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= 2;
    }
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += 2;
    }
}

//描画
void Tank::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Tank::Release()
{
}
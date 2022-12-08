#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

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

    Debug::Log("angle =");
    Debug::Log(transform_.rotate_.y, true);

    //戦車の現在地をベクトル型に変換
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //1フレームの移動ベクトル
    XMVECTOR vMove{ 0.0f, 0.0f, 0.1f, 0.0f };   //奥に0.1m

    //transform_.rotate_.y度回転させる行列を作成
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //移動ベクトルを変形（戦車と同じ向きに回転）させる
    vMove = XMVector3TransformCoord(vMove, mRotY);

    //Wキーが押されたら
    if (Input::IsKey(DIK_W))
    {
        //移動
        vPos += vMove;

        //現在地をベクトルからいつものtranform_.position_に戻す
        XMStoreFloat3(&transform_.position_, vPos);
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
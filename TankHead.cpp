#include "TankHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Bullet.h"

//�R���X�g���N�^
TankHead::TankHead(GameObject* parent)
    :GameObject(parent, "TankHead"), hModel_(-1)
{
}

//�f�X�g���N�^
TankHead::~TankHead()
{
}

//������
void TankHead::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("TankHead.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void TankHead::Update()
{
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 2;
    }
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 2;
    }

    if (Input::IsKeyDown(DIK_SPACE))
    {
        XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
        XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");
        XMVECTOR vTop = XMLoadFloat3(&cannonTop);
        XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);
        XMVECTOR vMove = vTop - vRoot;
        vMove = XMVector3Normalize(vMove);
        vMove *= 0.1f;
        XMFLOAT3 move;
        XMStoreFloat3(&move, vMove);


        Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
        pBullet->SetPosition(cannonTop);
        pBullet->SetMove(move);
    }
}

//�`��
void TankHead::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void TankHead::Release()
{
}
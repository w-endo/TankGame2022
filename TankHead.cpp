#include "TankHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

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
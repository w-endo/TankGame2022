#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Tank::Tank(GameObject* parent)
    :GameObject(parent, "Tank"), hModel_(-1)
{
}

//�f�X�g���N�^
Tank::~Tank()
{
}

//������
void Tank::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("TankBody.fbx");
    assert(hModel_ >= 0);
}

//�X�V
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

//�`��
void Tank::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Tank::Release()
{
}
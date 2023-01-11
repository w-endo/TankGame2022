#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet"),
    hModel_(-1)
{
}

//�f�X�g���N�^
Bullet::~Bullet()
{
}

//������
void Bullet::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Bullet.fbx");
    assert(hModel_ >= 0);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3f);
    AddCollider(collision);
}

//�X�V
void Bullet::Update()
{
    transform_.position_.x += move_.x;
    transform_.position_.y += move_.y;
    transform_.position_.z += move_.z;


    move_.y -= 0.01f;

    if (transform_.position_.z > 50.0f)
    {
        KillMe();
    }
}

//�`��
void Bullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Bullet::Release()
{
}
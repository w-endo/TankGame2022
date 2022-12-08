#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

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

    Debug::Log("angle =");
    Debug::Log(transform_.rotate_.y, true);

    //��Ԃ̌��ݒn���x�N�g���^�ɕϊ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //1�t���[���̈ړ��x�N�g��
    XMVECTOR vMove{ 0.0f, 0.0f, 0.1f, 0.0f };   //����0.1m

    //transform_.rotate_.y�x��]������s����쐬
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //�ړ��x�N�g����ό`�i��ԂƓ��������ɉ�]�j������
    vMove = XMVector3TransformCoord(vMove, mRotY);

    //W�L�[�������ꂽ��
    if (Input::IsKey(DIK_W))
    {
        //�ړ�
        vPos += vMove;

        //���ݒn���x�N�g�����炢����tranform_.position_�ɖ߂�
        XMStoreFloat3(&transform_.position_, vPos);
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
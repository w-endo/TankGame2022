#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "Ground.h"

enum
{
    CAM_TYPE_FIXED,       //�Œ�
    CAM_TYPE_TPS_NO_ROT,  //�O�l�́i��]�����j
    CAM_TYPE_TPS,         //�O�l��
    CAM_TYPE_FPS,         //��l��
    CAM_TYPE_MAX
};


//�R���X�g���N�^
Tank::Tank(GameObject* parent)
    :GameObject(parent, "Tank"), hModel_(-1), camType_(CAM_TYPE_TPS_NO_ROT)
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

    if (Input::IsKeyDown(DIK_Z))
    {
        camType_++;
        if (camType_ == CAM_TYPE_MAX)
        {
            camType_ = 0;
        }
    }


    switch (camType_)
    {
    case CAM_TYPE_FIXED:
    {
        Camera::SetTarget(XMFLOAT3(0, 0, 0));
        Camera::SetPosition(XMFLOAT3(0, 20, -30));
        break;
    }

    case CAM_TYPE_TPS_NO_ROT:
    {
        Camera::SetTarget(transform_.position_);
        XMFLOAT3 camPos = transform_.position_;
        camPos.y += 5;
        camPos.z -= 10;
        Camera::SetPosition(camPos);
        break;
    }

    case CAM_TYPE_TPS:
    {
        Camera::SetTarget(transform_.position_);
        XMVECTOR vCam = { 0, 5, -10, 0 };
        vCam = XMVector3TransformCoord(vCam, mRotY);
        XMFLOAT3 camPos;
        XMStoreFloat3(&camPos, vPos + vCam);
        Camera::SetPosition(camPos);
        break;
    }

    case CAM_TYPE_FPS:
    {
        Camera::SetPosition(transform_.position_);
        XMFLOAT3 camTarget;
        XMStoreFloat3(&camTarget, vPos + vMove);
        Camera::SetTarget(camTarget);
        break;
    }
    }


    Ground* pGround = (Ground*)FindObject("Ground");
    int hGroundModel = pGround->GetModelHandle();

    RayCastData data;
    data.start = transform_.position_;   //���C�̔��ˈʒu
    data.start.y = 0;
    data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &data); //���C�𔭎�

    if (data.hit == true)
    {
        transform_.position_.y = -data.dist;
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
#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class TankHead : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    TankHead(GameObject* parent);

    //�f�X�g���N�^
    ~TankHead();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    int GetModelHandle() { return hModel_; }
};
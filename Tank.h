#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Tank : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Tank(GameObject* parent);

    //�f�X�g���N�^
    ~Tank();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};
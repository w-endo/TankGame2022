#include "PlayScene.h"
#include "Tank.h"
#include "Ground.h"
#include "Enemy.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Tank>(this);
	Instantiate<Ground>(this);
	Instantiate<Enemy>(this);
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
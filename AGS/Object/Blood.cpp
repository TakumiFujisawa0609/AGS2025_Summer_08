#include <DxLib.h>
#include <cmath>
#include "Blood.h"

void Blood::Init()
{
	//imageId_ = LoadGraph("Data/Effect/blood.png", true);

    isAlive_ = false;
}

void Blood::Update()
{

    if (!isAlive_) return;

    bool anyAlive = false;


    for (int i = 0; i < PARTICLE_NUM; i++) {
        Particle& p = particles_[i];

        if (p.life > 0.0f) {
            // 重力効果（落ちる）
            p.dir.y -= 0.08f;

            // 摩擦・減速
            p.dir.x *= 0.96f;
            p.dir.z *= 0.96f;

            // 位置更新
            p.pos = VAdd(p.pos, VScale(p.dir, p.speed));

            // 寿命
            p.life -= 1.0f / 60.0f;
            if (p.life > 0.0f) anyAlive = true;
        }
    }

    if (!anyAlive) {
        isAlive_ = false;
    }

}

void Blood::Draw()
{

    //DrawFormatString(500, 200, 0xffffff, "isAliveB:%d", isAlive_);
    //if (!isAlive_) return;                                                                    

    //for (int i = 0; i < PARTICLE_NUM; i++) {
    //    const Particle& p = particles_[i];
    //    if (p.life > 0.0f) {
    //        float alpha = p.life / MAX_LIFE;
    //        int red = 255;
    //        int alphaColor = (int)(255 * alpha);
    //        int color = GetColor(red, 0, 0);

    //        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaColor);
    //        DrawSphere3D(p.pos, p.scale * 0.3f, 4, color, color, TRUE);
    //        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    //    }
    //}
}

void Blood::Release()
{
    /*if (imageId_ != -1) {
        DeleteGraph(imageId_);
        imageId_ = -1;
    }*/
}

void Blood::Emit()
{
    for (int i = 0; i < PARTICLE_NUM; i++) {
        particles_[i].pos = origin_;

        // 弾の進行方向ベースのバラけた方向
        float yaw = GetRand(360) * DX_PI / 180.0f;
        float pitch = (GetRand(60) - 30) * DX_PI / 180.0f; // 上下 ±30°

        VECTOR dir;
        dir.x = cosf(pitch) * cosf(yaw);
        dir.y = sinf(pitch);
        dir.z = cosf(pitch) * sinf(yaw);
        dir = VNorm(dir);

        particles_[i].dir = dir;
        particles_[i].life = MAX_LIFE; 
        particles_[i].scale = SCALE + GetRand(25); 
        particles_[i].speed = SPEED + GetRand(50) / 10.0f;  
    }
}

void Blood::SetPos(VECTOR pos)
{
    origin_ = pos;
}

void Blood::SetAlive(bool isAlive)
{
	isAlive_ = isAlive;
}

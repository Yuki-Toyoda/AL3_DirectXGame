#include "WorldTransform.h"
#include "math/MyMath.h"

void WorldTransform::UpdateMatrix() {

	// スケール、回転、平行移動を合成して行列を計算
	matWorld_ = MyMath::MakeAffineMatrix(scale_, rotation_, translation_);

	// 親があれば親のワールド行列を掛ける
	if (parent_) {
		matWorld_ = MyMath::Multiply(matWorld_, parent_->matWorld_);
	}

	// 行列を転送
	TransferMatrix();

}